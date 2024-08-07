// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Global/ContentsEnum.h"
#include "BossMonsterDataRow.generated.h"

class UAnimMontage;

USTRUCT()
struct UNREAL5_PORTFOLIO_API FRangedAttackRange
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Min = 0.0f;

	UPROPERTY(EditAnywhere)
	float Max = 0.0f;
};


USTRUCT(BlueprintType)
struct FBossMonsterDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	// 공격 데미지
	UPROPERTY(EditAnywhere)
	float MeleeAttackDamage = 20.0f;

	// 근접 공격 범위
	UPROPERTY(EditAnywhere)
	float MeleeAttackRange = 0.0f;

	// 원거리 공격 범위 
	UPROPERTY(EditAnywhere)
	FRangedAttackRange RangedAttackRange;

	// 투사체 공격력
	UPROPERTY(EditAnywhere)
	float ProjectileDamage = 10.0f;

	// 추격 속도
	UPROPERTY(EditAnywhere)
	float ChaseSpeed = 0.0f;

	// 몽타주
	UPROPERTY(EditAnywhere)
	TMap<EBossMonsterAnim, class UAnimMontage*> AnimMontages;
};
