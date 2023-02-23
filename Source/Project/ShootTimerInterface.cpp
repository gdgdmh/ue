// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTimerInterface.h"

// Add default functionality here for any IShootTimerInterface functions that are not pure virtual.
UShootTimerInterface::UShootTimerInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void IShootTimerInterface::SetShootTimerEnable(bool bIsEnable)
{
	(void)bIsEnable;
}

void IShootTimerInterface::SetShootTimer(float Interval)
{
	(void)Interval;
}

// パラメーター
void IShootTimerInterface::SetShootParameter(TObjectPtr<AVsShootParameter> Parameter)
{
	(void)Parameter;
}

bool IShootTimerInterface::StartShootTimer(FTimerManager& TimerManager)
{
	(void)TimerManager;
	return true;
}

void IShootTimerInterface::ProcessShoot()
{
}

void IShootTimerInterface::OnShootTimerElapsed()
{
}