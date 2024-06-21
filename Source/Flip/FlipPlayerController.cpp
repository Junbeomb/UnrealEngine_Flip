// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlipPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "FlipCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AFlipPlayerController::AFlipPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AFlipPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AFlipPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started, this, &AFlipPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &AFlipPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Completed, this, &AFlipPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Canceled, this, &AFlipPlayerController::OnSetDestinationReleased);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFlipPlayerController::Move);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AFlipPlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	APawn* ControlledPawn = GetPawn();

	if (bMouseClick) {
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y/3);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X/3);
	}
	else {
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AFlipPlayerController::OnInputStarted()
{
	StopMovement();
	bMouseClick = true;
}

// Triggered every frame when the input is held down
void AFlipPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		APawn* ControlledPawn = GetPawn();
		FVector Direction = Hit.Location - ControlledPawn->GetActorLocation();
		Direction.Z = 0;
		Direction.Normalize();
		FRotator TargetRotation = Direction.Rotation();
		FRotator CurrentRotation = ControlledPawn->GetActorRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 10.f); // 5.0f is the interpolation speed
		ControlledPawn->SetActorRotation(TargetRotation);
		//ControlledPawn->AddActorLocalRotation(TargetRotation);

		CachedDestination = Hit.Location;
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
	
	// Move towards mouse pointer or touch
	//APawn* ControlledPawn = GetPawn();
	//if (ControlledPawn != nullptr)
	//{
	//	FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
	//	ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	//}
}

void AFlipPlayerController::OnSetDestinationReleased()
{
	bMouseClick = false;
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		
	}

	FollowTime = 0.f;
}


