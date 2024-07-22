// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_GhostBase.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"

#include "BaseGhost.h"
#include "Hero/FlipCharacter.h"


AAIC_GhostBase::AAIC_GhostBase() {
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 500.f;
	SightConfig->LoseSightRadius = 600.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());

	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AAIC_GhostBase::OnPerceptionUpdated);
}

void AAIC_GhostBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	BGhost = Cast<ABaseGhost>(InPawn);
	if (IsValid(BGhost->BehaviorTree)) {
		RunBehaviorTree(BGhost->BehaviorTree);
	}

	//LinkMonster 블랙 보드에도 전달
	//AActor* tempActor = Cast<AActor>(BGhost->LinkMonster);
	GetBlackboardComponent()->SetValueAsObject(FName("LinkMonsterActor"), BGhost->LinkMonster);

}

void AAIC_GhostBase::SetStateAsAttacking(AActor* ATarget, bool useLastKnownAttackTarget)
{
	AActor* NewAttackTarget;
	//이전 Target이 있으면
	if (useLastKnownAttackTarget && AttackTarget) {
		NewAttackTarget = AttackTarget;
	}
	else {
		NewAttackTarget = ATarget;
	}

	GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), NewAttackTarget);

	//타겟 설정
	AttackTarget = NewAttackTarget;
}

void AAIC_GhostBase::SetStateAsHell()
{
	GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), nullptr);
}

void AAIC_GhostBase::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	if (UpdatedActors.Num() > 0)
	{
		SetStateAsAttacking(UpdatedActors[0], false);
	}
}

