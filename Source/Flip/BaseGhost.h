// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseGhost.generated.h"

UCLASS()
class FLIP_API ABaseGhost : public ACharacter
{
	GENERATED_BODY()

	class UCharacterMovementComponent* MovementComponent;

private://AI

	class AAIC_GhostBase* AIC_GhostBase;

public://AI

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAIController> AIControllerChoice;

public: //Link
	ABaseGhost();

	UPROPERTY(EditAnywhere)
	AActor* LinkMonster;

protected:
	virtual void BeginPlay() override;


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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
