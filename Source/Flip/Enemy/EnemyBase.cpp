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
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); //ĳ���Ϳ� �ִϸ��̼� blueprint�� �����Ǿ� �־�� �Ѵ�.

	if (AnimInstance && BasicAttackMontage) {
		AnimInstance->Montage_Play(BasicAttackMontage);
		// Montage ���� �� ȣ��Ǵ� ��������Ʈ�� �Լ� ���ε�
		FOnMontageEnded EndDelegate;
		EndDelegate.BindLambda([this](UAnimMontage* Montage, bool bInterrupted) {
			D_AttackEnd.Execute();
		});
		AnimInstance->Montage_SetEndDelegate(EndDelegate, BasicAttackMontage);
		//notify �� ���۵Ǿ��� ��
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

