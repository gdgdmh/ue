// Fill out your copyright notice in the Description page of Project Settings.


#include "LoopShootTimer.h"

ULoopShootTimer::ULoopShootTimer()
	: bIsShootTimerEnable(true)
	, Timer(1.0f)
{
}

ULoopShootTimer::~ULoopShootTimer()
{
}

// 発射タイマーの有効化、無効化
void ULoopShootTimer::SetShootTimerEnable(bool bIsEnable)
{
	bIsShootTimerEnable = bIsEnable;
}

// 発射間隔の設定
void ULoopShootTimer::SetShootTimer(float interval)
{
	check(interval >= 0.0f);
	Timer = interval;
}

// 発射タイマーの開始
bool ULoopShootTimer::StartShootTimer()
{
	if (!bIsShootTimerEnable)
	{
		return false;
	}
	UWorld* World = GetWorld();
	World->GetTimerManager().SetTimer(TimerHandle, this, &ULoopShootTimer::OnShootTimerElapsed, Timer, false);
	return true;
}

// 発射処理
void ULoopShootTimer::ProcessShoot()
{
}

// 発射タイマー経過時処理
void ULoopShootTimer::OnShootTimerElapsed()
{
	if (!bIsShootTimerEnable)
	{
		return;
	}
	ProcessShoot();
	StartShootTimer();
}