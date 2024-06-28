// Fill out your copyright notice in the Description page of Project Settings.


#include "ReverseCenter.h"

// Sets default values
AReverseCenter::AReverseCenter()
	:
	ReverseTime(1.f),
	ReverseSpeed(ReverseDegree / ReverseTime),
	reverseFlag(false),
	reversingDeltaSum(0.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������ �ʱ�ȭ���� 1.f �� ���⼱ 3.f�� editor���� 5.f�� �����ߴٸ�, ReverseSpeed�� ���� ���⼭ �θ��� 60.f, Beginplay���� Log�ϸ� 36�� ����.
	// �� Editor���� �ʱ�ȭ�ϴ°� �����ڿ� �ݿ��ȴ�.
	// Editor���� �����ϰ������ ReverseSpeed�� �����ִ� ���� BeginPlay() �� �־�� �Ѵ�.
	// ReverseTime = 3.f;
	// ReverseSpeed = ReverseDegree / ReverseTime;
}

void AReverseCenter::BeginPlay()
{
	Super::BeginPlay();

	ReverseSpeed = ReverseDegree / ReverseTime;
}

void AReverseCenter::CallReverse()
{
	reverseFlag = true;
	UE_LOG(LogTemp, Warning, TEXT("Center CallReverse"));
	D_ReverseStart.Broadcast();
}

void AReverseCenter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//ReverseTime ��ŭ ������ �ð�
	if (reverseFlag) {

		UE_LOG(LogTemp, Warning, TEXT("%f"), reversingDeltaSum);
		reversingDeltaSum += DeltaTime;
		if (reversingDeltaSum >= ReverseTime) {
			reverseFlag = false;
			reversingDeltaSum = 0.f;
			D_ReverseEnd.Broadcast();
		}
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

