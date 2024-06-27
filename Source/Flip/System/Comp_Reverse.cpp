#include "Comp_Reverse.h"
#include "Flip/Hero/FlipCharacter.h"
#include "Kismet/GameplayStatics.h"



UComp_Reverse::UComp_Reverse()
{

	PrimaryComponentTick.bCanEverTick = true;

	isReverse = false;
}


void UComp_Reverse::BeginPlay()
{
	Super::BeginPlay();

	Hero = Cast<AFlipCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	Hero->Comp_ReverseCenter->D_ReverseStart.AddUObject(this, &UComp_Reverse::ReverseStart);
	Hero->Comp_ReverseCenter->D_ReverseEnd.AddUObject(this, &UComp_Reverse::ReverseEnd);

	reverseSpeed = Hero->Comp_ReverseCenter->GetReverseSpeed();
}


void UComp_Reverse::ReverseStart()
{
	isReverse = true;
}

void UComp_Reverse::ReverseEnd()
{
	isReverse = false;
	//GetOwner()->SetActorRotation({ 0,0,180.f });
}


void UComp_Reverse::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isReverse) {
		float speed = reverseSpeed * DeltaTime;
		UE_LOG(LogTemp, Warning, TEXT("%f"), reverseSpeed);
		FRotator tempR =GetOwner()->GetActorRotation();
		//GetOwner()->SetActorRotation({ 0,0,tempR.Roll + speed }); //Pitch,Yaw,Roll
		GetOwner()->SetActorRelativeRotation({ 0,0,tempR.Roll + speed }); //Pitch,Yaw,Roll
	}

}

