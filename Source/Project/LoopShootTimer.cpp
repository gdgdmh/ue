// Fill out your copyright notice in the Description page of Project Settings.


#include "LoopShootTimer.h"

ALoopShootTimer::ALoopShootTimer()
	: bIsShootTimerEnable(true)
	, Timer(1.0f)
{
	//ShootParameter = NewObject<AVsShootParameter>();
}

ALoopShootTimer::ALoopShootTimer(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bIsShootTimerEnable(true)
	, Timer(1.0f)
{
	ShootParameter = ObjectInitializer.CreateDefaultSubobject<AVsShootParameter>(this, TEXT("AVsShootParameter"));
}

ALoopShootTimer::~ALoopShootTimer()
{
}

// 発射タイマーの有効化、無効化
void ALoopShootTimer::SetShootTimerEnable(bool bIsEnable)
{
	bIsShootTimerEnable = bIsEnable;
}

// 発射間隔の設定
void ALoopShootTimer::SetShootTimer(float interval)
{
	check(interval >= 0.0f);
	Timer = interval;
}

// パラメーター設定
void ALoopShootTimer::SetShootParameter(TObjectPtr<AVsShootParameter> Parameter)
{
	//ShootParameter->Copy(Parameter);
}

// 発射タイマーの開始
bool ALoopShootTimer::StartShootTimer(FTimerManager& TimerManager)
{
	if (!bIsShootTimerEnable)
	{
		return false;
	}
	TimerManager.SetTimer(TimerHandle, this, &ALoopShootTimer::OnShootTimerElapsed, Timer, false);
	return true;
}

// 発射処理
void ALoopShootTimer::ProcessShoot()
{
}

// 発射タイマー経過時処理
void ALoopShootTimer::OnShootTimerElapsed()
{
	if (!bIsShootTimerEnable)
	{
		return;
	}
	ProcessShoot();
	UWorld* World = /*GEngine->*/ GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Log, TEXT("StartShootTimer Failure World nullptr"));
		return;
	}
	StartShootTimer(World->GetTimerManager());
}