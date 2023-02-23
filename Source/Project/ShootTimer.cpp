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

// ���˃^�C�}�[�̗L�����A������
void UShootTimer::SetShootTimerEnable(bool bIsEnable)
{
	bIsShootTimerEnable = bIsEnable;
}

// ���ˊԊu�̐ݒ�
void UShootTimer::SetShootTimer(float interval)
{
	check(interval >= 0.0f);
	Timer = interval;
}

// ���˃^�C�}�[�̊J�n
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

// ���ˏ���
void UShootTimer::ProcessShoot()
{
}

// ���˃^�C�}�[�o�ߎ�����
void UShootTimer::OnShootTimerElapsed()
{
	if (!bIsShootTimerEnable)
	{
		return;
	}
	ProcessShoot();
}