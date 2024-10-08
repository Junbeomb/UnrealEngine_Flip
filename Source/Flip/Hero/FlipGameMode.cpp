// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlipGameMode.h"
#include "FlipPlayerController.h"
#include "FlipCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFlipGameMode::AFlipGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AFlipPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/0_TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/0_TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}