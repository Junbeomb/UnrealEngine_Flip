// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FLIP_API E_HeroStatus
{
public:
	E_HeroStatus();
	~E_HeroStatus();
};

UENUM(BlueprintType)
enum class EHeroStatus : uint8
{
	RealBody UMETA(DisplayName = "RealBody"),
	Reversing UMETA(DisplayName = "Reversing"),
	GhostBody UMETA(DisplayName = "GhostBody")
};
