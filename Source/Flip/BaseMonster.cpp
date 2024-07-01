// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Math/UnrealMathUtility.h"

#include "System/ReverseCenter.h"
#include "System/ReverseFloor.h"

#include "AIC_Base.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"



// Sets default values
ABaseMonster::ABaseMonster()
	:
	deltaSum(0.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = GetCharacterMovement();

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

	//aicontroller 설정
	if (AIControllerChoice) {
		AIC_Base = Cast<AAIC_Base>(AIControllerChoice);
		AIControllerClass = AIControllerChoice;
		AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	}
}

void ABaseMonster::ReverseStart()
{
	//MovementComponent->SetActive(false);
	MovementComponent->GravityScale = 0.f;
	MovementComponent->MaxAcceleration = 1.f;
		//MovementComponent->SetGravityDirection({ 0,0,GetGravityDirection().Z *-1});
	this->AttachToActor(RFloor,FAttachmentTransformRules::KeepWorldTransform);
	//MovementComponent->SetGravityDirection({ 0,0,GetGravityDirection().Z *-1});
	rememR = GetGravityDirection();

	isReverse = true;
}

void ABaseMonster::ReverseEnd()
{

	MovementComponent->GravityScale = 1.f;
	MovementComponent->ResetMoveState();
	MovementComponent->MaxAcceleration = 2048.f;
	if (RCenter->E_RCenter_b == ERCenter::Real) {
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

