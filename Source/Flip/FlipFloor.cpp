// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipFloor.h"
#include "FlipManager.h"




// Sets default values
AFlipFloor::AFlipFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	RootComponent = FloorMesh;

}

// Called when the game starts or when spawned
void AFlipFloor::BeginPlay()
{
	Super::BeginPlay();

	FlipManager = Cast<AFlipManager>(GetComponentByClass(AFlipManager::StaticClass()));
	if(FlipManager)
		FlipManager->D_Flip.AddUObject(this, &AFlipFloor::DoFlip);
}

void AFlipFloor::DoFlip()
{
	UE_LOG(LogTemp, Warning, TEXT("FlipFloor : DoFlip"));
}

// Called every frame
void AFlipFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

