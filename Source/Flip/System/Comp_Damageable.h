// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Comp_Damageable.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLIP_API UComp_Damageable : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	float maxHP;
	UPROPERTY()
	float currentHP;

	UFUNCTION()
	void OwnerDie();

public:	
	UComp_Damageable();

	UFUNCTION()
	void InitHP();

	UFUNCTION()
	bool DamagedActor(float amount);
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
