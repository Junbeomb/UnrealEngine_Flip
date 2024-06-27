#include "Comp_Reverse.h"
#include "Flip/Hero/FlipCharacter.h"
#include "Kismet/GameplayStatics.h"



UComp_Reverse::UComp_Reverse()
{

	PrimaryComponentTick.bCanEverTick = true;

	isReverse = false;
	ReverseTime = 1.f;
}


void UComp_Reverse::BeginPlay()
{
	Super::BeginPlay();

	reverseSpeed = 180.f / ReverseTime;
	Hero = Cast<AFlipCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	Hero->D_Reverse.AddUObject(this, &UComp_Reverse::ReverseStart);
}


void UComp_Reverse::ReverseStart()
{
	isReverse = true;
}


void UComp_Reverse::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isReverse) {
		float speed = reverseSpeed * DeltaTime;

		FRotator tempR =GetOwner()->GetActorRotation();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *tempR.ToString());

		GetOwner()->SetActorRotation({ 0,0,tempR.Roll + speed }); //Pitch,Yaw,Roll
		
		if (tempR.Roll + speed >= 180.f) {
			GetOwner()->SetActorRotation({ 0,0,180.f });
			isReverse = false;
		}
	}

}

