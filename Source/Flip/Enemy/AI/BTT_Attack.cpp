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
    if (AIController == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    // Controlled Pawn 가져오기
    APawn* ControlledPawn = AIController->GetPawn();
    if (ControlledPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    UE_LOG(LogTemp, Warning, TEXT("Executing My Task"));
    // 여기에 작업을 수행하는 코드를 작성합니다.
    AEnemyBase* Enemy = Cast<AEnemyBase>(ControlledPawn);
    Enemy->BasicAttack();

    // 작업이 성공적으로 완료되었음을 알립니다.
    return EBTNodeResult::Succeeded;

}
