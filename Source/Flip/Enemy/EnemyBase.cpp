// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

#include "../System/Comp_Damageable.h"



// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Comp_Damage = CreateDefaultSubobject<UComp_Damageable>(TEXT("Comp_Damage"));
}

void AEnemyBase::BasicAttack()
{
	//UE_LOG(LogTemp, Warning, TEXT("BasicAttack _Parent!!!!!"));
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); //캐릭터에 애니메이션 blueprint가 설정되어 있어야 한다.

	if (AnimInstance && BasicAttackMontage) {
		AnimInstance->Montage_Play(BasicAttackMontage);
		// Montage 종료 시 호출되는 델리게이트에 함수 바인딩
		FOnMontageEnded EndDelegate;
		EndDelegate.BindLambda([this](UAnimMontage* Montage, bool bInterrupted) {
			D_AttackEnd.Execute();
		});
		AnimInstance->Montage_SetEndDelegate(EndDelegate, BasicAttackMontage);
		//notify 가 시작되었을 때
		//AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AEnemyBase::OnNotifyBossCombo1);
	}
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

