// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTimer.h"

UShootTimer::UShootTimer()
	: bIsShootTimerEnable(true)
	, Timer(1.0f)
{
}

UShootTimer::UShootTimer(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bIsShootTimerEnable(true)
	, Timer(1.0f)
{
	ShootParameter = ObjectInitializer.CreateDefaultSubobject<AVsShootParameter>(this, TEXT("AVsShootParameter"));
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

// �p�����[�^�[�ݒ�
void UShootTimer::SetShootParameter(TObjectPtr<AVsShootParameter> Parameter)
{
	//ShootParameter->Copy(Parameter);
}

// ���˃^�C�}�[�̊J�n
bool UShootTimer::StartShootTimer(FTimerManager& TimerManager)
{
	if (!bIsShootTimerEnable)
	{
		return false;
	}
	TimerManager.SetTimer(TimerHandle, this, &UShootTimer::OnShootTimerElapsed, Timer, false);
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