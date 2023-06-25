// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoopShootTimer.h"
#include "LoopShootWeaponBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoopShootBeforeDispacher);

/**
 * 
 */
UCLASS()
class PROJECT_API ALoopShootWeaponBase : public ALoopShootTimer
{
	GENERATED_BODY()
public:
	ALoopShootWeaponBase();
	ALoopShootWeaponBase(const class FObjectInitializer& ObjectInitializer);
	
	~ALoopShootWeaponBase();

	// override IShootTimerInterface
public:
	// 発射前処理
	virtual void ProcessShootBefore() override;

public:

	FLoopShootBeforeDispacher& GetShootBeforeDispacher() { return ShootBeforeDispacher; }

protected:
	UPROPERTY(BlueprintAssignable)
		FLoopShootBeforeDispacher ShootBeforeDispacher;
};
