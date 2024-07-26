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


#include "../System/ReverseCenter.h"



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
	UE_LOG(LogTemp, Warning, TEXT("Player BasicAttack"));

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); //캐릭터에 애니메이션 blueprint가 설정되어 있어야 한다.
	if (AnimInstance && BasicAttackMontage) {
		AnimInstance->Montage_SetPlayRate(BasicAttackMontage,2.f);
		AnimInstance->Montage_Play(BasicAttackMontage);
		//notify 가 시작되었을 때
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AFlipCharacter::OnNotifyEndAttack);
	}
}

void AFlipCharacter::OnNotifyEndAttack(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	if (NotifyName == "EndAttack") {
		D_AttackEnd.Execute();
		UE_LOG(LogTemp, Warning, TEXT("Player BasicAttack End!!!!!!!!"));
	}
}

void AFlipCharacter::ReverseStart()
{
	HeroState = EHeroStatus::Reversing;

	LaunchCharacter({ 0,0,100.f/RCenter->GetReverseTime()}, true, true);
	GetCharacterMovement()->GravityScale = 0.f;
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	UE_LOG(LogTemp, Warning, TEXT("FlipCharacter : CallD_Reverse "));
}

void AFlipCharacter::ReverseEnd()
{
	GetCharacterMovement()->GravityScale = 1.0f;
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	UE_LOG(LogTemp, Warning, TEXT("FlipCharacter : ReverseEnd"));
}
