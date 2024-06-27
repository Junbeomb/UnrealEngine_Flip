#include "Comp_ReverseCenter.h"

UComp_ReverseCenter::UComp_ReverseCenter() 
	: 
	ReverseTime(1.f),
	ReverseSpeed(ReverseDegree/ReverseTime),
	reverseFlag(false),
	reversingDeltaSum(0.f)
{
	PrimaryComponentTick.bCanEverTick = true;

	//생성자 초기화에서 1.f 로 여기선 3.f로 editor에선 5.f로 적용했다면, ReverseSpeed의 값을 여기서 부르면 60.f, Beginplay에서 Log하면 36이 나옴.
	//즉 editor에서 초기화하는건 생성자에 반영안댐.
	// editor에서 적용하고싶으면 ReverseSpeed를 정해주는 식이 BeginPlay() 에 있어야 한다.
	//ReverseTime = 3.f;
	//ReverseSpeed = ReverseDegree / ReverseTime;
}



void UComp_ReverseCenter::BeginPlay()
{
	Super::BeginPlay();

	ReverseSpeed = ReverseDegree / ReverseTime;

	UE_LOG(LogTemp, Warning, TEXT("ReverseSpeed : %f"), ReverseSpeed);
	
}

void UComp_ReverseCenter::CallReverse()
{
	D_ReverseStart.Broadcast();
	reverseFlag = true;
}

float UComp_ReverseCenter::GetReverseSpeed()
{
	return ReverseDegree/ReverseTime;
}

void UComp_ReverseCenter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//ReverseTime 만큼 뒤집는 시간
	if (reverseFlag) {
		reversingDeltaSum += DeltaTime;
		if (reversingDeltaSum >= ReverseTime) {
			reverseFlag = false;
			reversingDeltaSum = 0.f;
			D_ReverseEnd.Broadcast();
		}
	}
}

