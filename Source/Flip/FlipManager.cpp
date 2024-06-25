// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipManager.h"

// Sets default values
AFlipManager::AFlipManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFlipManager::DFlipExecute()
{
	D_Flip.Broadcast();
}

// Called when the game starts or when spawned
void AFlipManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlipManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

