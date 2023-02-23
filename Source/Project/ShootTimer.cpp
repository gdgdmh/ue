// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTimer.h"

UShootTimer::UShootTimer()
	: bIsShootTimerEnable(true)
	, Timer(1.0f)
{
}

UShootTimer::~UShootTimer()
{
}

// 発射タイマーの有効化、無効化
void UShootTimer::SetShootTimerEnable(bool bIsEnable)
{
	bIsShootTimerEnable = bIsEnable;
}

// 発射間隔の設定
void UShootTimer::SetShootTimer(float interval)
{
	check(interval >= 0.0f);
	Timer = interval;
}

// 発射タイマーの開始
bool UShootTimer::StartShootTimer()
{
	if (!bIsShootTimerEnable)
	{
		return false;
	}
	UWorld* World = GetWorld();
	World->GetTimerManager().SetTimer(TimerHandle, this, &UShootTimer::OnShootTimerElapsed, Timer, false);
	return true;
}

// 発射処理
void UShootTimer::ProcessShoot()
{
}

// 発射タイマー経過時処理
void UShootTimer::OnShootTimerElapsed()
{
	if (!bIsShootTimerEnable)
	{
		return;
	}
	ProcessShoot();
}