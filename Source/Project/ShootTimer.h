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
	UShootTimer(const class FObjectInitializer& ObjectInitializer);
	~UShootTimer();

	// override IShootTimerInterface
public:
	// ���˃^�C�}�[�̗L�����A������
	virtual void SetShootTimerEnable(bool bIsEnable) override;
	// ���ˊԊu�̐ݒ�
	virtual void SetShootTimer(float interval) override;
	// �p�����[�^�[�ݒ�
	virtual void SetShootParameter(TObjectPtr<AVsShootParameter> Parameter) override;
	// ���˃^�C�}�[�̊J�n
	virtual bool StartShootTimer(FTimerManager& TimerManager) override;
	// ���ˏ���
	virtual void ProcessShoot();
	// ���˃^�C�}�[�o�ߎ�����
	virtual void OnShootTimerElapsed()  override;

private:
	FTimerHandle TimerHandle;
	TObjectPtr<AVsShootParameter> ShootParameter;
	bool bIsShootTimerEnable;
	float Timer;
};
