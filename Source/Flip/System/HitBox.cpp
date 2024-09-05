// Fill out your copyright notice in the Description page of Project Settings.


#include "HitBox.h"
#include "Components/SphereComponent.h"



AHitBox::AHitBox()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->SetSphereRadius(80.f);
	SphereComp->SetHiddenInGame(false);

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AHitBox::OnSphereBeginOverlap);


}

void AHitBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHitBox::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Collide  : %s"), *OtherActor->GetName());

}


