// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "E_HeroStatus.h"

#include "FlipCharacter.generated.h"

DECLARE_DELEGATE(FD_AttackEnd);

UCLASS(Blueprintable)
class AFlipCharacter : public ACharacter
{
	GENERATED_BODY()

	EHeroStatus HeroState;

	class AReverseCenter* RCenter;

private://Controller
	UPROPERTY()
	class AFlipPlayerController* FlipPlayerController;


public://Animation
	FD_AttackEnd D_AttackEnd;


private: // Animation

	UPROPERTY(EditAnywhere)
	class UAnimMontage* BasicAttackMontage;

	UPROPERTY()
	UAnimInstance* AnimInstance;

	UFUNCTION()
	void OnNotifyEndAttack(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	

public://Attack

	UFUNCTION()
	void BasicAttack();

public://Reverse
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

	virtual void BeginPlay() override;

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

