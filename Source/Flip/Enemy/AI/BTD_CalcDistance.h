// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_CalcDistance.generated.h"

/**
 * 
 */
UCLASS()
class FLIP_API UBTD_CalcDistance : public UBTDecorator
{
	GENERATED_BODY()
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

public:
	UBTD_CalcDistance();

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Target;// ≈∏∞Ÿ ø¢≈Õ


	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector AttackRange; //¿˚¡§ ∞≈∏Æ

	UPROPERTY(EditAnywhere)
	float errorMargin;

};
