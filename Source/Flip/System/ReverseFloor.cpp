
#include "ReverseFloor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DirectionalLight.h" 
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Math/UnrealMathUtility.h"
//#include "C:\Program Files\Epic Games\UE_5.4\Engine\Source\Runtime\Engine\Classes\Components\SkyAtmosphereComponent.h"

#include "ReverseCenter.h"


AReverseFloor::AReverseFloor()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	RootComponent = FloorMesh;
	//AttributeTimeline
	AttributeTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("MaterialTimeline"));
	MaterialTimelineCallback.BindUFunction(this, FName("MaterialTimelineUpdate"));
	LightTimelineCallback.BindUFunction(this, FName("LightTimelineUpdate"));
	AttributeTimelineFinishedCallback.BindUFunction(this, FName("MaterialTimelineFinish"));
	//RTimeline
	RTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("RTimeline"));
	RTimelineCallback.BindUFunction(this, FName("RTimelineUpdate"));
	RTimelineFinishedCallback.BindUFunction(this, FName("RTimelineFinish"));
}



void AReverseFloor::BeginPlay()
{
	Super::BeginPlay();

	RCenter =Cast<AReverseCenter>(UGameplayStatics::GetActorOfClass(GetWorld(), AReverseCenter::StaticClass()));
	RCenter->D_ReverseStart.AddUObject(this, &AReverseFloor::ReverseStart);
	RCenter->D_ReverseEnd.AddUObject(this, &AReverseFloor::ReverseEnd);

	reverseSpeed = RCenter->GetReverseSpeed();

	DMI = FloorMesh->CreateDynamicMaterialInstance(0, FloorMesh->GetMaterial(0));

	DLight = Cast<ADirectionalLight>(UGameplayStatics::GetActorOfClass(GetWorld(), ADirectionalLight::StaticClass()));
	SkyAtmos = Cast<ASkyAtmosphere>(UGameplayStatics::GetActorOfClass(GetWorld(), ASkyAtmosphere::StaticClass()));
	
}

void AReverseFloor::ReverseStart()
{
	isReverse = true;
	startRotation = GetActorRotation().Roll;
	//RTimeline
	if (RCurve) {
		RTimeline->AddInterpFloat(RCurve, RTimelineCallback, FName("RTimeline"));
		RTimeline->SetTimelineFinishedFunc(RTimelineFinishedCallback);
		RTimeline->SetPlayRate(1/ RCenter->GetReverseTime());
		RTimeline->PlayFromStart();
	}
}

void AReverseFloor::ReverseEnd()
{
	isReverse = false;

	//AttributeTimeline
	if (MaterialCurve && LightCurve) {
		AttributeTimeline->AddInterpFloat(MaterialCurve, MaterialTimelineCallback, FName("Material"));
		AttributeTimeline->AddInterpFloat(LightCurve, LightTimelineCallback, FName("Light"));

		AttributeTimeline->SetTimelineFinishedFunc(AttributeTimelineFinishedCallback);
		AttributeTimeline->SetPlayRate(0.3f);
		AttributeTimeline->PlayFromStart();
	}
}


// Called every frame
void AReverseFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//뒤집기
void AReverseFloor::RTimelineUpdate(float Value)
{
	SetActorRotation({ 0,0,startRotation + Value * 180.f });
}
void AReverseFloor::RTimelineFinish()
{
}

void AReverseFloor::MaterialTimelineUpdate(float Value)
{
	if (DMI) {
		if (RCenter->E_RCenter == ERCenter::Hell) {
			DMI->SetScalarParameterValue(FName("Progress"), Value * 2.f); //0까지 1로 만들려면 2를 곱해야함
		}
		else {
			DMI->SetScalarParameterValue(FName("Progress"), 2.f-(Value * 2.f)); 
		}
	}
}

void AReverseFloor::LightTimelineUpdate(float Value)
{
	if (RCenter->E_RCenter == ERCenter::Hell) {
		DLight->GetLightComponent()->SetLightColor(FMath::Lerp(LightColor_Real, LightColor_Hell, Value));
		SkyAtmos->GetComponent()->SetRayleighScattering(FMath::Lerp(Atmos_Real, Atmos_Hell, Value));
	}
	else {
		DLight->GetLightComponent()->SetLightColor(FMath::Lerp(LightColor_Hell, LightColor_Real, Value));
		SkyAtmos->GetComponent()->SetRayleighScattering(FMath::Lerp(Atmos_Hell, Atmos_Real, Value));
	}
	
}

void AReverseFloor::AttributeTimelineFinish()
{
}


