// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Comp_Reverse.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLIP_API UComp_Reverse : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	class AFlipCharacter* Hero;

private: //Reverse
	UFUNCTION()
	void ReverseStart();

	UPROPERTY(EditAnywhere)
	bool isReverse;

	float tickSumReverse;

	UPROPERTY(EditAnywhere)
	float reverseSpeed;

public:	
	// Sets default values for this component's properties
	UComp_Reverse();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
