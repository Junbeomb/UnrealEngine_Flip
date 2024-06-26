// Fill out your copyright notice in the Description page of Project Settings.


#include "ReverseFloor.h"
#include "Comp_Reverse.h"

// Sets default values
AReverseFloor::AReverseFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	RootComponent = FloorMesh;

	Comp_Reverse = CreateDefaultSubobject<UComp_Reverse>(TEXT("Comp_Reverse"));

}

// Called when the game starts or when spawned
void AReverseFloor::BeginPlay()
{
	Super::BeginPlay();

}

void AReverseFloor::DoFlip()
{
	UE_LOG(LogTemp, Warning, TEXT("AReverseFloor : DoFlip"));
}

// Called every frame
void AReverseFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

