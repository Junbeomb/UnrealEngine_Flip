// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Kismet/GameplayStatics.h"

#include "ReverseCenter.generated.h"


UENUM(BlueprintType)
enum class ERCenter : uint8
{
	Real UMETA(DisplayName = "Real"),
	Reversing UMETA(DisplayName = "Reversing"),
	Hell UMETA(DisplayName = "Hell")
};

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

	float reverseCallCoolTime;


public:
	AReverseCenter();

	ERCenter E_RCenter;
	ERCenter E_RCenter_b;

	F_Reverse D_ReverseStart;
	F_Reverse D_ReverseEnd;

	void CallReverse();

	float GetReverseSpeed();

	float GetReverseTime();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

};
