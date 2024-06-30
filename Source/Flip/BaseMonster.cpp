// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "System/ReverseCenter.h"
#include "System/ReverseFloor.h"

#include "AIC_Base.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"



// Sets default values
ABaseMonster::ABaseMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = GetCharacterMovement();


}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	
	RCenter = Cast<AReverseCenter>(UGameplayStatics::GetActorOfClass(GetWorld(), AReverseCenter::StaticClass()));
	if (RCenter) {
		RCenter->D_ReverseStart.AddUObject(this, &ABaseMonster::ReverseStart);
		RCenter->D_ReverseEnd.AddUObject(this, &ABaseMonster::ReverseEnd);
	}
	RFloor = Cast<AReverseFloor>(UGameplayStatics::GetActorOfClass(GetWorld(), AReverseFloor::StaticClass()));

	//aicontroller ¼³Á¤
	if (AIControllerChoice) {
		AIControllerClass = AIControllerChoice;
		AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	}
}

void ABaseMonster::ReverseStart()
{
	this->AttachToActor(RFloor, FAttachmentTransformRules::KeepWorldTransform);
	MovementComponent->GravityScale = 0.f;

		MovementComponent->SetGravityDirection({ 0,0,GetGravityDirection().Z *-1});
	//if (RCenter->E_RCenter_b == ERCenter::Hell) {//Hell->Real ·Î 
	//}
	//else {
	//	MovementComponent->SetGravityDirection({ 0,0,1 });
	//}

	isReverse = true;
}

void ABaseMonster::ReverseEnd()
{
	MovementComponent->GravityScale = 1.f;
	this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, [this]() {
	//}, 0.1f, false);

	isReverse = false;
}

// Called every frame
void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

