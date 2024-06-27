#include "Comp_ReverseCenter.h"

UComp_ReverseCenter::UComp_ReverseCenter() 
	: 
	ReverseTime(1.f),
	ReverseSpeed(ReverseDegree/ReverseTime),
	reverseFlag(false),
	reversingDeltaSum(0.f)
{
	PrimaryComponentTick.bCanEverTick = true;

	//������ �ʱ�ȭ���� 1.f �� ���⼱ 3.f�� editor���� 5.f�� �����ߴٸ�, ReverseSpeed�� ���� ���⼭ �θ��� 60.f, Beginplay���� Log�ϸ� 36�� ����.
	//�� editor���� �ʱ�ȭ�ϴ°� �����ڿ� �ݿ��ȴ�.
	// editor���� �����ϰ������ ReverseSpeed�� �����ִ� ���� BeginPlay() �� �־�� �Ѵ�.
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

	//ReverseTime ��ŭ ������ �ð�
	if (reverseFlag) {
		reversingDeltaSum += DeltaTime;
		if (reversingDeltaSum >= ReverseTime) {
			reverseFlag = false;
			reversingDeltaSum = 0.f;
			D_ReverseEnd.Broadcast();
		}
	}
}

