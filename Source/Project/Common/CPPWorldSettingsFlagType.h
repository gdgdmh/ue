// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPWorldSettingsFlagType.generated.h"

UENUM(BlueprintType)
enum class EWorldSettingsFlagType : uint8
{
	UseUserWidgetSubsystem		UMETA(DisplayName = "UserWidgetSubsystem使用フラグ", ToolTip = "UserWidgetSubsystem"),
	UseEnemySpawnSubsystem		UMETA(DisplayName = "UseEnemySpawnSubsystem使用フラグ", ToolTip = "UseEnemySpawnSubsystem"),

	Num				UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EWorldSettingsFlagType, EWorldSettingsFlagType::Num)
