// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

UCLASS()
class FLIP_API ABaseActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;


private:
	class AReverseCenter* RCenter;
	class AReverseFloor* RFloor;

	bool isReverse;

	float reverseSpeed;

	void ReverseStart();

	void ReverseEnd();

	FTimerHandle DelayTimerHandle;

public:	
	// Sets default values for this actor's properties
	ABaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
