// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGhost.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Math/UnrealMathUtility.h"

#include "System/ReverseCenter.h"
#include "System/ReverseFloor.h"

#include "BaseMonster.h"

// Sets default values
ABaseGhost::ABaseGhost()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent =GetCharacterMovement();

	MovementComponent->SetGravityDirection({ 0, 0,1 });
	MovementComponent->bUseControllerDesiredRotation = true;


}

// Called when the game starts or when spawned
void ABaseGhost::BeginPlay()
{
	Super::BeginPlay();
	
	RCenter = Cast<AReverseCenter>(UGameplayStatics::GetActorOfClass(GetWorld(), AReverseCenter::StaticClass()));
	if (RCenter) {
		RCenter->D_ReverseStart.AddUObject(this, &ABaseGhost::ReverseStart);
		RCenter->D_ReverseEnd.AddUObject(this, &ABaseGhost::ReverseEnd);
	}
	RFloor = Cast<AReverseFloor>(UGameplayStatics::GetActorOfClass(GetWorld(), AReverseFloor::StaticClass()));

	
}

void ABaseGhost::ReverseStart()
{
	MovementComponent->GravityScale = 0.f;
	MovementComponent->MaxAcceleration = 1.f;
	this->AttachToActor(RFloor, FAttachmentTransformRules::KeepWorldTransform);

	rememR = GetGravityDirection();

}

void ABaseGhost::ReverseEnd()
{

	MovementComponent->GravityScale = 1.f;
	MovementComponent->ResetMoveState();
	MovementComponent->MaxAcceleration = 2048.f;
	MovementComponent->SetGravityDirection({ 0, 0, GetGravityDirection().Z * -1 });

	/*if (RCenter->E_RCenter == ERCenter::Real) {
		GetMesh()->SetVisibility(false);
	}
	else if (RCenter->E_RCenter == ERCenter::Hell) {
		GetMesh()->SetVisibility(true);
	}*/
}

// Called every frame
void ABaseGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LinkMonster) {
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *LinkMonster->GetActorLocation().ToString());
		
		//SetActorLocation({ LinkMonster->GetActorLocation().X,LinkMonster->GetActorLocation().Y,LinkMonster->GetActorLocation().Z * -1 });
	}
}

