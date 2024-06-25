// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlipManager.generated.h"


DECLARE_MULTICAST_DELEGATE(F_FlipExecute);

UCLASS()
class FLIP_API AFlipManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlipManager();

	F_FlipExecute D_Flip;

	UFUNCTION()
	void DFlipExecute();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
