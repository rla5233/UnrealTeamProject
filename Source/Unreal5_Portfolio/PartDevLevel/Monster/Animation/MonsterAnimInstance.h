// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Animation/MainAnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UMonsterAnimInstance : public UMainAnimInstance
{
	GENERATED_BODY()

public:
	template<typename EnumType>
	void PushRandomAnimation(EnumType _Key, FAnimMontageGroup _MontageGroup)
	{
		PushRandomAnimation(static_cast<uint8>(_Key), _MontageGroup);
	}
	
	UFUNCTION(Reliable, Server)
	void PushRandomAnimation(uint8 _Key, FAnimMontageGroup _MontageGroup);
	void PushRandomAnimation_Implementation(uint8 _Key, FAnimMontageGroup _MontageGroup);

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UFUNCTION(Reliable, NetMulticast)
	void PushMontage(uint8 _Key, FAnimMontageGroup _MontageGroup);
	void PushMontage_Implementation(uint8 _Key, FAnimMontageGroup _MontageGroup);

private:
	UPROPERTY(Replicated)
	int RandomIndex = -1;

};