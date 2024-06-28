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

	// 생성자 초기화에서 1.f 로 여기선 3.f로 editor에선 5.f로 적용했다면, ReverseSpeed의 값을 여기서 부르면 60.f, Beginplay에서 Log하면 36이 나옴.
	// 즉 Editor에서 초기화하는건 생성자에 반영안댐.
	// Editor에서 적용하고싶으면 ReverseSpeed를 정해주는 식이 BeginPlay() 에 있어야 한다.
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
	//ReverseTime 만큼 뒤집는 시간
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

