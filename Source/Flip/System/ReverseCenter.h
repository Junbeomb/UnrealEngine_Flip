// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Kismet/GameplayStatics.h"

#include "ReverseCenter.generated.h"

DECLARE_MULTICAST_DELEGATE(F_Reverse);
UCLASS()
class FLIP_API AReverseCenter : public AActor
{
	GENERATED_BODY()

	const float ReverseDegree = 180.f;

	UPROPERTY(EditAnywhere)
	float ReverseTime;

	float ReverseSpeed;

	bool reverseFlag;
	float reversingDeltaSum;

public:
	AReverseCenter();

	F_Reverse D_ReverseStart;
	F_Reverse D_ReverseEnd;

	void CallReverse();

	float GetReverseSpeed();

	float GetReverseTime();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
