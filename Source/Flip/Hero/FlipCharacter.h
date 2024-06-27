// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "E_HeroStatus.h"
#include "Comp_ReverseCenter.h"

#include "FlipCharacter.generated.h"


UCLASS(Blueprintable)
class AFlipCharacter : public ACharacter
{
	GENERATED_BODY()

	EHeroStatus HeroState;



public:

	UPROPERTY(EditAnywhere)
	UComp_ReverseCenter* Comp_ReverseCenter;

	UFUNCTION()
	void ReverseStart();
	UFUNCTION()
	void ReverseEnd();

public:
	AFlipCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

public:

	UFUNCTION()
	void CallD_Reverse();

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};

