// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../EnemyBase.h"

#include "BaseMonster.generated.h"


UCLASS()
class FLIP_API ABaseMonster : public AEnemyBase
{
	GENERATED_BODY()

	class UCharacterMovementComponent* MovementComponent;

public://basic command

	virtual void BasicAttack() override;

private://AI

	//class AAIC_MonsterBase* AIC_Base;

public://AI

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BehaviorTree;

	//UPROPERTY(EditAnywhere)
	//TSubclassOf<class AAIController> AIControllerChoice;

private: //Reverse
	class AReverseCenter* RCenter;
	class AReverseFloor* RFloor;

	bool isReverse;

	void ReverseStart();
	void ReverseEnd();

	FTimerHandle DelayTimerHandle;

	float deltaSum;
	FVector rememR;

private: //Ghost
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABaseGhost> LinkGhost;
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* GhostBehaviorTree;

public: //Basic
	ABaseMonster();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
