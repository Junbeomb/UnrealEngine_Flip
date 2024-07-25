// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_CalcDistance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTD_CalcDistance::UBTD_CalcDistance()
{
	errorMargin = 10.f;
}

bool UBTD_CalcDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{

	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName));
	
	if (TargetActor) {
		float distance = TargetActor->GetDistanceTo(OwnerComp.GetAIOwner()->GetPawn());
		//distance -= errorMargin;

		float IdealDistance = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(AttackRange.SelectedKeyName);
		UE_LOG(LogTemp, Warning, TEXT("Distance : %f"),distance);
		UE_LOG(LogTemp, Warning, TEXT("Ideal Distance : %f"),IdealDistance);
		return distance <= IdealDistance;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Distance Over"));
	return false;
}


