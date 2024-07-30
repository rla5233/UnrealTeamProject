// Fill out your copyright notice in the Description page of Project Settings.


#include "PartDevLevel/Monster/Mutant/AI/MyBTTaskNode_MutantChase.h"
#include "PartDevLevel/Monster/TestMonsterBaseAIController.h"
#include "PartDevLevel/Monster/TestMonsterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Global/ContentsLog.h"

EBTNodeResult::Type UMyBTTaskNode_MutantChase::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	if (false == Monster->IsValidLowLevel())
	{
		LOG(MonsterLog, Fatal, TEXT("%S(%u)> Monster Is Not Valid"));
		return EBTNodeResult::Type::Aborted;
	}

	UTestMonsterData* MonsterData = GetValueAsObject<UTestMonsterData>(_OwnerComp, TEXT("MonsterData"));
	Monster->GetCharacterMovement()->MovementMode = EMovementMode::MOVE_NavWalking;
	Monster->GetCharacterMovement()->MaxWalkSpeed = Monster->GetBaseData()->GetRunSpeed();
	Monster->ChangeRandomAnimation(ETestMonsterAnim::Run);

	return EBTNodeResult::Type::InProgress;
}

void UMyBTTaskNode_MutantChase::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	if (ETestMonsterState::Chase != static_cast<ETestMonsterState>(GetCurState(_OwnerComp)))
	{
		FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
		return;
	}

	UTestMonsterData* MonsterData = GetValueAsObject<UTestMonsterData>(_OwnerComp, TEXT("MonsterData"));
	ATestMonsterBase* Monster = GetActor<ATestMonsterBase>(_OwnerComp);
	FVector MonsterLocation = Monster->GetActorLocation();

	AActor* TargetActor = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));
	FVector TargetLocation = TargetActor->GetActorLocation();

	EPathFollowingRequestResult::Type IsMove = Monster->GetAIController()->MoveToLocation(TargetLocation);

	// 범위 안에 있으면 공격상태로 변경
	FVector LocationDiff = TargetLocation - MonsterLocation;
	double DiffLength = LocationDiff.Size();
	if (DiffLength <= MonsterData->AttackBoundary)
	{
		StateChange(_OwnerComp, ETestMonsterState::Attack);
		return;
	}
	else if (DiffLength <= MonsterData->JumpAttackBoundary)
	{
		StateChange(_OwnerComp, ETestMonsterState::JumpAttack);
		return;
	}

}
