// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Attack.h"
#include "AIController.h"
#include "../EnemyBase.h"



UBTT_Attack::UBTT_Attack()
{
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    // AI Controller 가져오기
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr) return EBTNodeResult::Failed;

    // Controlled Pawn 가져오기
    APawn* ControlledPawn = AIController->GetPawn();
    if (ControlledPawn == nullptr) return EBTNodeResult::Failed;


    //Attack 실행
    AEnemyBase* Enemy = Cast<AEnemyBase>(ControlledPawn);
    Enemy->BasicAttack();
    //Attack End 시
    Enemy->D_AttackEnd.BindLambda([&OwnerComp, this]() { 
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        });

    //Montage 실행 중
    return EBTNodeResult::InProgress;
}
