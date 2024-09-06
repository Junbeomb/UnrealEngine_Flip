// Fill out your copyright notice in the Description page of Project Settings.


#include "Comp_Damageable.h"



UComp_Damageable::UComp_Damageable()
{
	PrimaryComponentTick.bCanEverTick = false;
	maxHP = 100.f;
	currentHP = maxHP;
}


void UComp_Damageable::BeginPlay()
{
	Super::BeginPlay();
}

void UComp_Damageable::InitHP()
{
	currentHP = maxHP;
}

bool UComp_Damageable::DamagedActor(float amount)
{
	currentHP -= amount;

	if (currentHP <= 0) { 
		OwnerDie();//자신에게 알려주기
		return true; //죽으면 때린놈 에게도 알려주기
	}

	return false;
}

void UComp_Damageable::OwnerDie()
{
	GetOwner()->Destroy();
}


void UComp_Damageable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

