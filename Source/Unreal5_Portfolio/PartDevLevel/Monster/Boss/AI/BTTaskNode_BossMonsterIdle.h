// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PartDevLevel/Monster/Boss/AI/BTTaskNode_BossMonster.h"
#include "BTTaskNode_BossMonsterIdle.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBTTaskNode_BossMonsterIdle : public UBTTaskNode_BossMonster
{
	GENERATED_BODY()

public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComponent, uint8* _NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& _OwnerComponent, uint8* _pNodeMemory, float _DeltaSeconds) override;
};
