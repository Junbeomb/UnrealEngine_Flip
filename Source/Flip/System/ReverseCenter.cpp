
#include "ReverseCenter.h"


//AReverseCenter는 순수히 뒤집어지는 기능에 대해서만
//환경의 변화는 Floor 에서.

AReverseCenter::AReverseCenter()
	:
	ReverseTime(1.f),
	reverseFlag(false),
	reversingDeltaSum(0.f),
	E_RCenter(ERCenter::Real),
	reverseCallCoolTime(0.f)
{
	PrimaryActorTick.bCanEverTick = true;

	// 생성자 초기화에서 1.f 로 여기선 3.f로 editor에선 5.f로 적용했다면, ReverseSpeed의 값을 여기서 부르면 60.f, Beginplay에서 Log하면 36이 나옴.
	// 즉 Editor에서 초기화하는건 생성자에 반영안댐.
	// Editor에서 적용하고싶으면 ReverseSpeed를 정해주는 식이 BeginPlay() 에 있어야 한다.
}

void AReverseCenter::BeginPlay()
{
	Super::BeginPlay();

	ReverseSpeed = ReverseDegree / ReverseTime;

}

void AReverseCenter::CallReverse()
{
	if (E_RCenter == ERCenter::Reversing) return;
	if (reverseCallCoolTime > 0.f) return;

	E_RCenter_b = E_RCenter;
	E_RCenter = ERCenter::Reversing;
	D_ReverseStart.Broadcast();
}

void AReverseCenter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ReverseTime 만큼 뒤집는 시간
	if (E_RCenter == ERCenter::Reversing) {
		reversingDeltaSum += DeltaTime;
		if (reversingDeltaSum >= ReverseTime) {
			reversingDeltaSum = 0.f;

			switch (E_RCenter_b) {
				case ERCenter::Real:
					E_RCenter = ERCenter::Hell;
					break;
				case ERCenter::Hell: 
					E_RCenter = ERCenter::Real;
					break;
			}

			//쿨타임
			reverseCallCoolTime = 3.f;

			D_ReverseEnd.Broadcast();
		}
	}

	if (reverseCallCoolTime > 0.f) {
		reverseCallCoolTime -= DeltaTime;
	}

}

float AReverseCenter::GetReverseSpeed()
{
	return ReverseDegree / ReverseTime;
}

float AReverseCenter::GetReverseTime()
{
	return ReverseTime;
}

