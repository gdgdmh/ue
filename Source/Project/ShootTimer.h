// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootTimerInterface.h"
#include "ShootTimer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UShootTimer : public UObject, public IShootTimerInterface
{
	GENERATED_BODY()

public:
	UShootTimer();
	~UShootTimer();

	// override IShootTimerInterface
public:
	// ���˃^�C�}�[�̗L�����A������
	virtual void SetShootTimerEnable(bool bIsEnable) override;
	// ���ˊԊu�̐ݒ�
	virtual void SetShootTimer(float interval) override;
	// ���˃^�C�}�[�̊J�n
	virtual bool StartShootTimer() override;
	// ���ˏ���
	virtual void ProcessShoot();
	// ���˃^�C�}�[�o�ߎ�����
	virtual void OnShootTimerElapsed()  override;

private:
	FTimerHandle TimerHandle;
	bool bIsShootTimerEnable;
	float Timer;
};
