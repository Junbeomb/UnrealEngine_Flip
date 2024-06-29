
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/TimelineComponent.h"

#include "ReverseFloor.generated.h"


UCLASS()
class FLIP_API AReverseFloor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* FloorMesh;

	UMaterialInstanceDynamic* DMI;

	class ADirectionalLight* DLight;
	UPROPERTY(EditAnywhere)
	FLinearColor LightColor_Real;
	UPROPERTY(EditAnywhere)
	FLinearColor LightColor_Hell;
	class ASkyAtmosphere* SkyAtmos;
	UPROPERTY(EditAnywhere)
	FLinearColor Atmos_Real;
	UPROPERTY(EditAnywhere)
	FLinearColor Atmos_Hell;

public:
	AReverseFloor();

private: //Reverse
	class AReverseCenter* RCenter;

	bool isReverse;

	float reverseSpeed;

	void ReverseStart();

	void ReverseEnd();

	float startRotation;

private: //Timeline

	UPROPERTY(EditAnywhere, Category = Timeline)
	UTimelineComponent* AttributeTimeline;

	//AttributeTimeline
		//그래프
	UPROPERTY(EditAnywhere, Category = Timeline);
	UCurveFloat* MaterialCurve;
	UPROPERTY(EditAnywhere, Category = Timeline);
	UCurveFloat* LightCurve;
	//업데이트
	FOnTimelineFloat MaterialTimelineCallback;
	UFUNCTION()
	void MaterialTimelineUpdate(float Value);
	FOnTimelineFloat LightTimelineCallback;
	UFUNCTION()
	void LightTimelineUpdate(float Value);
	// 종료시
	FOnTimelineEvent AttributeTimelineFinishedCallback;
	UFUNCTION()
	void AttributeTimelineFinish();

	UPROPERTY(EditAnywhere, Category = Timeline)
	UTimelineComponent* RTimeline;

	//RTimeline
		//그래프
	UPROPERTY(EditAnywhere, Category = Timeline);
	UCurveFloat* RCurve;
	//업데이트
	FOnTimelineFloat RTimelineCallback;
	UFUNCTION()
	void RTimelineUpdate(float Value);
	// 종료시
	FOnTimelineEvent RTimelineFinishedCallback;
	UFUNCTION()
	void RTimelineFinish();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
