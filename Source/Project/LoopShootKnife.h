// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoopShootWeaponBase.h"
#include "LoopShootKnife.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ALoopShootKnifer : public ALoopShootWeaponBase
{
	GENERATED_BODY()

public:
	ALoopShootKnifer();
	ALoopShootKnifer(const class FObjectInitializer& ObjectInitializer);
	~ALoopShootKnifer();
public:

	// override IShootTimerInterface
public:
	// ���ˏ���
	virtual void ProcessShoot() override;

	UFUNCTION()
	void test() {}

private:

};