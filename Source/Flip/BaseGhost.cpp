// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGhost.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Math/UnrealMathUtility.h"

#include "System/ReverseCenter.h"
#include "System/ReverseFloor.h"

#include "AIC_GhostBase.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


#include "BaseMonster.h"

ABaseGhost::ABaseGhost()
{
	PrimaryActorTick.bCanEverTick = false;

	MovementComponent =GetCharacterMovement();

	MovementComponent->SetGravityDirection({ 0, 0,1 });
	MovementComponent->bUseControllerDesiredRotation = true;

	GetMesh()->SetVisibility(false);
}


void ABaseGhost::BeginPlay()
{
	Super::BeginPlay();
	
	RCenter = Cast<AReverseCenter>(UGameplayStatics::GetActorOfClass(GetWorld(), AReverseCenter::StaticClass()));
	if (RCenter) {
		RCenter->D_ReverseStart.AddUObject(this, &ABaseGhost::ReverseStart);
		RCenter->D_ReverseEnd.AddUObject(this, &ABaseGhost::ReverseEnd);
	}
	RFloor = Cast<AReverseFloor>(UGameplayStatics::GetActorOfClass(GetWorld(), AReverseFloor::StaticClass()));


	//aicontroller ¼³Á¤
	if (AIControllerChoice) {
		AIC_Base = Cast<AAIC_GhostBase>(AIControllerChoice);
		AIControllerClass = AIControllerChoice;
		AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	}
}

void ABaseGhost::ReverseStart()
{
	MovementComponent->GravityScale = 0.f;
	MovementComponent->MaxAcceleration = 1.f;
	this->AttachToActor(RFloor, FAttachmentTransformRules::KeepWorldTransform);

	rememR = GetGravityDirection();
}

void ABaseGhost::ReverseEnd()
{
	MovementComponent->GravityScale = 1.f;
	MovementComponent->ResetMoveState();
	MovementComponent->MaxAcceleration = 2048.f;
	MovementComponent->SetGravityDirection({ 0, 0, GetGravityDirection().Z * -1 });

	if (RCenter->E_RCenter == ERCenter::Real) {
		GetMesh()->SetVisibility(false);
	}
	else if (RCenter->E_RCenter == ERCenter::Hell) {
		GetMesh()->SetVisibility(true);
	}

	SetActorLocation({ LinkMonster->GetActorLocation().X,LinkMonster->GetActorLocation().Y, LinkMonster->GetActorLocation().Z * -1 });
}

// Called every frame
void ABaseGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

