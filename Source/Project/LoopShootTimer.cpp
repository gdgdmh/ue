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

// ���˃^�C�}�[�̗L�����A������
void ULoopShootTimer::SetShootTimerEnable(bool bIsEnable)
{
	bIsShootTimerEnable = bIsEnable;
}

// ���ˊԊu�̐ݒ�
void ULoopShootTimer::SetShootTimer(float interval)
{
	check(interval >= 0.0f);
	Timer = interval;
}

// ���˃^�C�}�[�̊J�n
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

// ���ˏ���
void ULoopShootTimer::ProcessShoot()
{
}

// ���˃^�C�}�[�o�ߎ�����
void ULoopShootTimer::OnShootTimerElapsed()
{
	if (!bIsShootTimerEnable)
	{
		return;
	}
	ProcessShoot();
	StartShootTimer();
}