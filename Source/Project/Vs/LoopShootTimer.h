// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootTimerInterface.h"
#include "LoopShootTimer.generated.h"



/**
 * 
 */
UCLASS()
class PROJECT_API ALoopShootTimer : public AActor, public IShootTimerInterface
{
	GENERATED_BODY()

public:
	ALoopShootTimer();
	ALoopShootTimer(const class FObjectInitializer& ObjectInitializer);

	~ALoopShootTimer();

	// override IShootTimerInterface
public:
	// 発射タイマーの有効化、無効化
	virtual void SetShootTimerEnable(bool bIsEnable) override;
	// 発射間隔の設定
	virtual void SetShootTimer(float interval) override;
	// パラメーター設定
	virtual void SetShootParameter(TObjectPtr<AVsShootParameter> Parameter) override;
	// 発射タイマーの開始
	virtual bool StartShootTimer(FTimerManager& TimerManager) override;

	// 発射処理
	virtual void ProcessShoot() override;
	// 発射タイマー経過時処理
	virtual void OnShootTimerElapsed()  override;

protected:
	FTimerHandle TimerHandle;
	TObjectPtr<AVsShootParameter> ShootParameter;
	bool bIsShootTimerEnable;
	float Timer;

};
