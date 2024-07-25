// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActor.h"
#include "ReverseCenter.h"
#include "ReverseFloor.h"

// Sets default values
ABaseActor::ABaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void ABaseActor::BeginPlay()
{
	Super::BeginPlay();
	
	RCenter = Cast<AReverseCenter>(UGameplayStatics::GetActorOfClass(GetWorld(), AReverseCenter::StaticClass()));
	if (RCenter) {
		RCenter->D_ReverseStart.AddUObject(this, &ABaseActor::ReverseStart);
		RCenter->D_ReverseEnd.AddUObject(this, &ABaseActor::ReverseEnd);
	}

	RFloor = Cast<AReverseFloor>(UGameplayStatics::GetActorOfClass(GetWorld(), AReverseFloor::StaticClass()));
}

void ABaseActor::ReverseStart()
{
	if (RCenter->E_RCenter_b == ERCenter::Real) { //Real->Hell로 넘어가기 시작
		BaseMesh->SetSimulatePhysics(false);
		this->AttachToActor(RFloor, FAttachmentTransformRules::KeepWorldTransform);
	}

	isReverse = true;
}

void ABaseActor::ReverseEnd()
{
	if (RCenter->E_RCenter_b == ERCenter::Hell) {//Hell->Real 로 넘어가기 끝
		GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, [this]() {
			BaseMesh->SetSimulatePhysics(true);
		}, 0.1f, false);
		this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}

	isReverse = false;
}

// Called every frame
void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

