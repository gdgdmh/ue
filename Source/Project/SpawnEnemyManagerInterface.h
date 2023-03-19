// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpawnEnemyManagerInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class USpawnEnemyManagerInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class PROJECT_API ISpawnEnemyManagerInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	virtual void Test();
};


/*
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UShootTimerInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class PROJECT_API IShootTimerInterface
{
	GENERATED_IINTERFACE_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 発射タイマーの有効化、無効化
	virtual void SetShootTimerEnable(bool bIsEnable);
	// 発射間隔の設定
	virtual void SetShootTimer(float Interval);
	// パラメーター設定
	virtual void SetShootParameter(TObjectPtr<AVsShootParameter> Parameter);
	// 発射タイマーの開始
	virtual bool StartShootTimer(FTimerManager& TimerManager);
	// 発射前処理
	virtual void ProcessShootBefore();
	// 発射処理
	virtual void ProcessShoot();
	// 発射タイマー経過時処理
	virtual void OnShootTimerElapsed();
};

*/
