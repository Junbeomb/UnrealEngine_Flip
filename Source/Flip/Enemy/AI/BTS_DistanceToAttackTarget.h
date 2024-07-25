// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_DistanceToAttackTarget.generated.h"

/**
 * 
 */
UCLASS()
class FLIP_API UBTS_DistanceToAttackTarget : public UBTService
{
	GENERATED_BODY()
	

public:
	UBTS_DistanceToAttackTarget();

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Target;// ≈∏∞Ÿ ø¢≈Õ

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Distance; //¿˚¡§ ∞≈∏Æ



	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
