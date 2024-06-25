// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlipFloor.generated.h"

UCLASS()
class FLIP_API AFlipFloor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* FloorMesh;

	UPROPERTY(EditDefaultsOnly)
	class AFlipManager* FlipManager;

	UFUNCTION()
	void DoFlip();

	
public:	
	// Sets default values for this actor's properties
	AFlipFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
