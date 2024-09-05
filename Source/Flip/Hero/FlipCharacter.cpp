// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlipCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"

#include "Materials/Material.h"
#include "Engine/World.h"
#include "../System/HitBox.h"
#include "DrawDebugHelpers.h"

#include "../System/ReverseCenter.h"
#include "FlipPlayerController.h"



AFlipCharacter::AFlipCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	

}

void AFlipCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	RCenter = Cast<AReverseCenter>(UGameplayStatics::GetActorOfClass(GetWorld(), AReverseCenter::StaticClass()));
	if (RCenter) {
		RCenter->D_ReverseStart.AddUObject(this, &AFlipCharacter::ReverseStart);
		RCenter->D_ReverseEnd.AddUObject(this, &AFlipCharacter::ReverseEnd);
	}

	//Animation
	AnimInstance = GetMesh()->GetAnimInstance(); //ĳ���Ϳ� �ִϸ��̼� blueprint�� �����Ǿ� �־�� �Ѵ�.
	if (!AnimInstance->OnPlayMontageNotifyBegin.IsAlreadyBound(this, &AFlipCharacter::OnNotifyBegin)) {
		//UE_LOG(LogTemp, Warning, TEXT("Notify Bound!!!!"));
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AFlipCharacter::OnNotifyBegin);
	}
	FlipPlayerController = Cast<AFlipPlayerController>(GetController());
}

void AFlipCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}


void AFlipCharacter::CallD_Reverse()
{
	RCenter->CallReverse();
}



void AFlipCharacter::BasicAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Player BasicAttack Continue!!!!!!!! : %d"), IsStopAttack);
	//�̹� �÷��� ���̸�
	if (AnimInstance->Montage_IsPlaying(BasicAttackMontage)) {
		//�޺� ���� ����
		if (IsStopAttack) {
			
			IsStopAttack = false;
		}
		return;
	}

	if (AnimInstance && BasicAttackMontage) {
		FlipPlayerController->restrictMove = true;

		//HItBox ����
		FVector Loc = GetActorLocation() + GetActorForwardVector() * 100;
		/*FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator(); 
		GetWorld()->SpawnActor<AHitBox>(AHitBox::StaticClass(), Loc, {0,0,0}, SpawnParams);*/

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this); // �ڱ� �ڽ��� �����մϴ�.

		// Sphere Trace ����
		bool bHit = GetWorld()->SweepSingleByChannel(
			HitResult,               
			GetActorLocation(),                     // ���� ��ġ
			Loc,                       // �� ��ġ
			FQuat::Identity,           // ȸ�� (��ü�̹Ƿ� ȸ���� �ʿ� ����)
			ECC_Visibility,            
			FCollisionShape::MakeSphere(80.f), 
			CollisionParams            
		);

		// ����׿� ���Ǿ�� ������ �׷� �ð������� Ȯ��
		DrawDebugLine(GetWorld(), GetActorLocation(), Loc, FColor::Blue, false, 2.0f, 0, 1.0f);
		DrawDebugSphere(GetWorld(), Loc, 80.f, 12, FColor::Green, false, 2.0f); 
		if (bHit) {
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult.GetActor()->GetName());
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20.f, 12, FColor::Red, false, 2.0f);
		}

		AnimInstance->Montage_Stop(0.1);
		AnimInstance->Montage_SetPlayRate(BasicAttackMontage,1.f);
		AnimInstance->Montage_Play(BasicAttackMontage);
	}
}

void AFlipCharacter::OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	if (NotifyName == "StartAttack") {
		IsStopAttack = true;
	}
	else if (NotifyName == "S_Combo") {

	}
	else if (NotifyName == "E_Combo") {
		if (IsStopAttack) {
			AnimInstance->Montage_Stop(0.0f);
			FlipPlayerController->restrictMove = false;
			UE_LOG(LogTemp, Warning, TEXT("Player BasicAttack End!!!!!!!!"));
		}
		else {
			
			IsStopAttack = true;
		}
	}
	else if (NotifyName == "EndAttack") {
		//D_AttackEnd.Execute();
		FlipPlayerController->restrictMove = false;
		//UE_LOG(LogTemp, Warning, TEXT("Player BasicAttack End!!!!!!!!"));
	}
	
}



void AFlipCharacter::ReverseStart()
{
	HeroState = EHeroStatus::Reversing;

	LaunchCharacter({ 0,0,100.f/RCenter->GetReverseTime()}, true, true);
	GetCharacterMovement()->GravityScale = 0.f;
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//UE_LOG(LogTemp, Warning, TEXT("FlipCharacter : CallD_Reverse "));
}

void AFlipCharacter::ReverseEnd()
{
	GetCharacterMovement()->GravityScale = 1.0f;
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//UE_LOG(LogTemp, Warning, TEXT("FlipCharacter : ReverseEnd"));
}
