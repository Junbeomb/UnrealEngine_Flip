// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_GhostBase.generated.h"

/**
 * 
 */
UCLASS()
class FLIP_API AAIC_GhostBase : public AAIController
{
	GENERATED_BODY()
	class ABaseGhost* BGhost;

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
	AAIC_GhostBase();

	UFUNCTION()
	void SetStateAsHell();
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
