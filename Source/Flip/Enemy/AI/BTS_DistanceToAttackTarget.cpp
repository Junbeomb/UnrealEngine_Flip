// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_DistanceToAttackTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTS_DistanceToAttackTarget::UBTS_DistanceToAttackTarget()
{
}

void UBTS_DistanceToAttackTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName));

	if (TargetActor) {
		float distance = TargetActor->GetDistanceTo(OwnerComp.GetAIOwner()->GetPawn());
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(Distance.SelectedKeyName, distance);
	}
}
