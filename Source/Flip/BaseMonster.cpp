// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Math/UnrealMathUtility.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "System/ReverseCenter.h"
#include "System/ReverseFloor.h"

#include "AIC_MonsterBase.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "BaseGhost.h"


// Sets default values
ABaseMonster::ABaseMonster()
	:
	deltaSum(0.f)
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = GetCharacterMovement();

	MovementComponent->SetGravityDirection({ 0, 0,-1 });
	MovementComponent->bUseControllerDesiredRotation = true;
	MovementComponent->MaxWalkSpeed = 200.f;
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	
	RCenter = Cast<AReverseCenter>(UGameplayStatics::GetActorOfClass(GetWorld(), AReverseCenter::StaticClass()));
	if (RCenter) {
		RCenter->D_ReverseStart.AddUObject(this, &ABaseMonster::ReverseStart);
		RCenter->D_ReverseEnd.AddUObject(this, &ABaseMonster::ReverseEnd);
	}
	RFloor = Cast<AReverseFloor>(UGameplayStatics::GetActorOfClass(GetWorld(), AReverseFloor::StaticClass()));

	//Ghost생성
	if (LinkGhost && GhostBehaviorTree) {
		
		FVector Location = { GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 500.f };
		FRotator Rotation = GetActorRotation();
		APawn* TempGhost = UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), LinkGhost, GhostBehaviorTree, Location, Rotation, true);
		ABaseGhost* Ghost = Cast<ABaseGhost>(TempGhost);

		if (Ghost) {
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetActorLocation().ToString());
			Ghost->LinkMonster = this;
		}
	}

	//aicontroller 설정
	if (AIControllerChoice) {
		AIC_Base = Cast<AAIC_MonsterBase>(AIControllerChoice);
		AIControllerClass = AIControllerChoice;
		AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	}
}

void ABaseMonster::ReverseStart()
{
	MovementComponent->GravityScale = 0.f;
	MovementComponent->MaxAcceleration = 1.f;
	this->AttachToActor(RFloor,FAttachmentTransformRules::KeepWorldTransform);

	isReverse = true;
}

void ABaseMonster::ReverseEnd()
{
	MovementComponent->GravityScale = 1.f;
	MovementComponent->ResetMoveState();
	MovementComponent->MaxAcceleration = 2048.f;
	if (RCenter->E_RCenter == ERCenter::Hell) {
		MovementComponent->SetGravityDirection({ 0, 0, GetGravityDirection().Z * -1 });
	}

	this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, [this]() {
		// 이동 컴포넌트 활성화 전에 위치와 회전 조정
		//MovementComponent->Activate(true);
	}, 1.f, false);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetActorRotation().ToString());
	deltaSum = 0.f;
	isReverse = false;
}

// Called every frame
void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ReverseEnd에서 하지 않는 이유는 바뀌는 동작이 보임. 돌아가는 중간에 바꿔야함.
	if (isReverse &&RCenter->E_RCenter_b == ERCenter::Hell) { 
		deltaSum += DeltaTime;
		if (deltaSum >= RCenter->GetReverseTime()/1.5) {
			isReverse = false;
			deltaSum = 0.f;
			MovementComponent->SetGravityDirection({ 0, 0, GetGravityDirection().Z * -1 });
			//isReverse = false;
			//deltaSum = 0.f;
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetGravityDirection().ToString());
		}
	}
}

