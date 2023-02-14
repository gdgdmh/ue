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

void IShootTimerInterface::SetShootTimer(float interval)
{
	(void)interval;
}

void IShootTimerInterface::OnShootTimerElapsed()
{
}