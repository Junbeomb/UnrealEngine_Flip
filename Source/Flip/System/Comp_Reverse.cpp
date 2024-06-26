#include "Comp_Reverse.h"
#include "Flip/Hero/FlipCharacter.h"
#include "Kismet/GameplayStatics.h"



UComp_Reverse::UComp_Reverse()
{

	PrimaryComponentTick.bCanEverTick = true;

}


void UComp_Reverse::BeginPlay()
{
	Super::BeginPlay();

	isReverse = false;
	reverseSpeed = 200.f;

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
		tickSumReverse += DeltaTime;

		float speed = reverseSpeed * DeltaTime;

		FRotator tempR =GetOwner()->GetActorRotation();

		GetOwner()->SetActorRelativeRotation({ tempR.Pitch + speed,0,0 });

		if (speed > 180.f) {
			isReverse = false;
		}
	}

}

