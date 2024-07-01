// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseMonster.generated.h"

UCLASS()
class FLIP_API ABaseMonster : public ACharacter
{
	GENERATED_BODY()

	class UCharacterMovementComponent* MovementComponent;

private://AI

	class AAIC_Base* AIC_Base;

public://AI

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAIController> AIControllerChoice;

private: //Reverse
	class AReverseCenter* RCenter;
	class AReverseFloor* RFloor;

	bool isReverse;

	void ReverseStart();
	void ReverseEnd();

	FTimerHandle DelayTimerHandle;

	float deltaSum;
	FVector rememR;


public:
	// Sets default values for this character's properties
	ABaseMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
