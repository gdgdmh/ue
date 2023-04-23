// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPVsUserWidgetType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EVsUserWidgetType : uint8
{
	None			UMETA(DisplayName = "�Ȃ�", ToolTip = "00:�Ȃ�"),
	DamageText		UMETA(DisplayName = "�_���[�W�e�L�X�g", ToolTip = "01:�_���[�W�e�L�X�g"),

	Num				UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EVsUserWidgetType, EVsUserWidgetType::Num)
