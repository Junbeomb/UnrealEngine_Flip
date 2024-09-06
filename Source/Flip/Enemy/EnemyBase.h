// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

DECLARE_DELEGATE(FD_AttackEnd);
UCLASS()

class FLIP_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()


private: // Animation

	UPROPERTY(EditAnywhere)
	class UAnimMontage* BasicAttackMontage;

	UPROPERTY()
	class UComp_Damageable* Comp_Damage;

public: //Animation

	FD_AttackEnd D_AttackEnd;

public:
	AEnemyBase();

	//기본 공격
	virtual void BasicAttack();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
