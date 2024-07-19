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

public:
	// Sets default values for this character's properties
	ABaseGhost();

	UPROPERTY()
	class ABaseMonster* LinkMonster;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABaseMonster> ChoiceLinkMonster;



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
