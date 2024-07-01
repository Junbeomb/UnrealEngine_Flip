// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_Base.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"


#include "BaseMonster.h"
#include "Hero/FlipCharacter.h"


AAIC_Base::AAIC_Base() {
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

	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AAIC_Base::OnPerceptionUpdated);
}

void AAIC_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	BMonster = Cast<ABaseMonster>(InPawn);
	if (IsValid(BMonster->BehaviorTree)) {
		RunBehaviorTree(BMonster->BehaviorTree);
	}
}

void AAIC_Base::SetStateAsAttacking(AActor* ATarget, bool useLastKnownAttackTarget)
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

void AAIC_Base::SetStateAsHell()
{
	GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), nullptr);
}

void AAIC_Base::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	if (UpdatedActors.Num() > 0)
	{
		SetStateAsAttacking(UpdatedActors[0], false);
	}
}
