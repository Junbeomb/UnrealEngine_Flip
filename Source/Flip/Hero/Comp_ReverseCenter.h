#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Comp_ReverseCenter.generated.h"

DECLARE_MULTICAST_DELEGATE(F_Reverse);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLIP_API UComp_ReverseCenter : public UActorComponent
{
	GENERATED_BODY()

	const float ReverseDegree = 180.f;

	UPROPERTY(EditAnywhere)
	float ReverseTime;

	float ReverseSpeed;

	bool reverseFlag;
	float reversingDeltaSum;

public:	
	UComp_ReverseCenter();

	F_Reverse D_ReverseStart;
	F_Reverse D_ReverseEnd;

	void CallReverse();

	float GetReverseSpeed();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
