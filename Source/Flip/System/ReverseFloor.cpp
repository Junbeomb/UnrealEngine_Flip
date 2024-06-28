// Fill out your copyright notice in the Description page of Project Settings.


#include "ReverseFloor.h"
#include "Kismet/GameplayStatics.h"
#include "ReverseCenter.h"
// Sets default values
AReverseFloor::AReverseFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	RootComponent = FloorMesh;
	//MaterialTimeline
	MaterialTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("MaterialTimeline"));
	MaterialTimelineCallback.BindUFunction(this, FName("MaterialTimelineUpdate"));
	MaterialTimelineFinishedCallback.BindUFunction(this, FName("MaterialTimelineFinish"));
}

void AReverseFloor::BeginPlay()
{
	Super::BeginPlay();

	RCenter =Cast<AReverseCenter>(UGameplayStatics::GetActorOfClass(GetWorld(), AReverseCenter::StaticClass()));
	RCenter->D_ReverseStart.AddUObject(this, &AReverseFloor::ReverseStart);
	RCenter->D_ReverseEnd.AddUObject(this, &AReverseFloor::ReverseEnd);

	reverseSpeed = RCenter->GetReverseSpeed();
	DMI = FloorMesh->CreateDynamicMaterialInstance(0, FloorMesh->GetMaterial(0));
}

void AReverseFloor::ReverseStart()
{
	isReverse = true;
	UE_LOG(LogTemp, Warning, TEXT("ReverseStart Floor"));
}

void AReverseFloor::ReverseEnd()
{

	isReverse = false;
	UE_LOG(LogTemp, Warning, TEXT("ReverseEnd Floor"));
	//ScaleTimeline
	if (MaterialCurve) {
		MaterialTimeline->AddInterpFloat(MaterialCurve, MaterialTimelineCallback, FName("MaterialTimeline"));
		MaterialTimeline->SetTimelineFinishedFunc(MaterialTimelineFinishedCallback);
		MaterialTimeline->SetPlayRate(0.3f);
		MaterialTimeline->PlayFromStart();
	}
}


// Called every frame
void AReverseFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isReverse) {
		float speed = reverseSpeed * DeltaTime;
		FRotator tempR = GetActorRotation();
		SetActorRelativeRotation({ 0,0,tempR.Roll + speed }); //Pitch,Yaw,Roll
	}
}

void AReverseFloor::MaterialTimelineUpdate(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("%f"), Value);
	if (DMI)
		DMI->SetScalarParameterValue(FName("Progress"), Value * 2.f); //0까지 1로 만들려면 2를 곱해야함
}

void AReverseFloor::MaterialTimelineFinish()
{
}


