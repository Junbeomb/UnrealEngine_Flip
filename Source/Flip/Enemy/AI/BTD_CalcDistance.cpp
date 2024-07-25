// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_CalcDistance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTD_CalcDistance::UBTD_CalcDistance()
{
	errorMargin = 50.f;
}

bool UBTD_CalcDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{

	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target->SelectedKeyName));
	
	float distance = TargetActor->GetDistanceTo(OwnerComp.GetAIOwner()->GetPawn());
	distance -= errorMargin;

	float IdealDistance = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(IdealRange->SelectedKeyName);
		
	return distance <= IdealDistance;
}


