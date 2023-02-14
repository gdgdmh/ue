// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ShootTimerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UShootTimerInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class PROJECT_API IShootTimerInterface
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// ���˃^�C�}�[�̗L�����A������
	virtual void SetShootTimerEnable(bool bIsEnable);
	// ���ˊԊu�̐ݒ�
	virtual void SetShootTimer(float interval);
	// ���˃^�C�}�[�o�ߎ�����
	virtual void OnShootTimerElapsed();
};
