// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Attack.h"
#include "AIController.h"
#include "../EnemyBase.h"



UBTT_Attack::UBTT_Attack()
{
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    // AI Controller ��������
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    // Controlled Pawn ��������
    APawn* ControlledPawn = AIController->GetPawn();
    if (ControlledPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    UE_LOG(LogTemp, Warning, TEXT("Executing My Task"));
    // ���⿡ �۾��� �����ϴ� �ڵ带 �ۼ��մϴ�.
    AEnemyBase* Enemy = Cast<AEnemyBase>(ControlledPawn);
    Enemy->BasicAttack();

    // �۾��� ���������� �Ϸ�Ǿ����� �˸��ϴ�.
    return EBTNodeResult::Succeeded;

}
