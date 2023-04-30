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
	None			UMETA(DisplayName = "なし", ToolTip = "00:なし"),
	DamageText		UMETA(DisplayName = "ダメージテキスト", ToolTip = "01:ダメージテキスト"),

	Num				UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EVsUserWidgetType, EVsUserWidgetType::Num)
