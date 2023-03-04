// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPEnemyType.generated.h"

/**
 * 
 */
/*
class PROJECT_API CPPEnemyType
{
public:
	CPPEnemyType();
	~CPPEnemyType();
};
*/

UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	Bat				UMETA(DisplayName = "�o�b�g",		ToolTip = "00:��������"),
	Skeleton		UMETA(DisplayName = "�X�P���g��",	ToolTip = "01:�X�P���g��"),

	Num				UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EEnemyType, EEnemyType::Num)
