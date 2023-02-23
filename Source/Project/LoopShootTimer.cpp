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

// ���˃^�C�}�[�̗L�����A������
void ALoopShootTimer::SetShootTimerEnable(bool bIsEnable)
{
	bIsShootTimerEnable = bIsEnable;
}

// ���ˊԊu�̐ݒ�
void ALoopShootTimer::SetShootTimer(float interval)
{
	check(interval >= 0.0f);
	Timer = interval;
}

// �p�����[�^�[�ݒ�
void ALoopShootTimer::SetShootParameter(TObjectPtr<AVsShootParameter> Parameter)
{
	//ShootParameter->Copy(Parameter);
}

// ���˃^�C�}�[�̊J�n
bool ALoopShootTimer::StartShootTimer(FTimerManager& TimerManager)
{
	if (!bIsShootTimerEnable)
	{
		return false;
	}
	TimerManager.SetTimer(TimerHandle, this, &ALoopShootTimer::OnShootTimerElapsed, Timer, false);
	return true;
}

// ���ˏ���
void ALoopShootTimer::ProcessShoot()
{
}

// ���˃^�C�}�[�o�ߎ�����
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