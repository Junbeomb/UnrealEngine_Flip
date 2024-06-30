// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIC_Base.generated.h"

UCLASS()
class FLIP_API AAIC_Base : public AAIController
{
	GENERATED_BODY()
	
	class ABaseMonster* BMonster;

	UPROPERTY()
	AActor* AttackTarget;
	UPROPERTY()
	class UAIPerceptionComponent* AIPerceptionComponent;
	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;


	UFUNCTION()
	void SetStateAsAttacking(AActor* ATarget, bool useLastKnownAttackTarget);

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

public:
	AAIC_Base();

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
