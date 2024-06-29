
#include "ReverseCenter.h"


//AReverseCenter�� ������ ���������� ��ɿ� ���ؼ���
//ȯ���� ��ȭ�� Floor ����.

AReverseCenter::AReverseCenter()
	:
	ReverseTime(1.f),
	reverseFlag(false),
	reversingDeltaSum(0.f),
	E_RCenter(ERCenter::Real),
	reverseCallCoolTime(0.f)
{
	PrimaryActorTick.bCanEverTick = true;

	// ������ �ʱ�ȭ���� 1.f �� ���⼱ 3.f�� editor���� 5.f�� �����ߴٸ�, ReverseSpeed�� ���� ���⼭ �θ��� 60.f, Beginplay���� Log�ϸ� 36�� ����.
	// �� Editor���� �ʱ�ȭ�ϴ°� �����ڿ� �ݿ��ȴ�.
	// Editor���� �����ϰ������ ReverseSpeed�� �����ִ� ���� BeginPlay() �� �־�� �Ѵ�.
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

	//ReverseTime ��ŭ ������ �ð�
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

			//��Ÿ��
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

