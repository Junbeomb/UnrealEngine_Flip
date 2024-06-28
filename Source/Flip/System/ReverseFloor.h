
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

	class AReverseCenter* RCenter;

public:
	AReverseFloor();

private: //Reverse

	bool isReverse;

	float reverseSpeed;

	UFUNCTION()
	void ReverseStart();

	UFUNCTION()
	void ReverseEnd();




private: //Timeline

	UPROPERTY(EditAnywhere, Category = Timeline)
	UTimelineComponent* MaterialTimeline;

	//MaterialTimeline
		//그래프
	UPROPERTY(EditAnywhere, Category = Timeline);
	UCurveFloat* MaterialCurve;
	//업데이트
	FOnTimelineFloat MaterialTimelineCallback;
	UFUNCTION()
	void MaterialTimelineUpdate(float Value);
	// 종료시
	FOnTimelineEvent MaterialTimelineFinishedCallback;
	UFUNCTION()
	void MaterialTimelineFinish();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
