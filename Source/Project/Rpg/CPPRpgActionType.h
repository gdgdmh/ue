// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPRpgActionType.generated.h"

/**
* 行動タイプ
*/
UENUM(BlueprintType)
enum class CPPRpgActionType : uint8
{
	None				UMETA(DisplayName = "なし",					ToolTip = "なし"),
	Attack				UMETA(DisplayName = "攻撃系",				ToolTip = "攻撃系"),
	Defence				UMETA(DisplayName = "防御系",				ToolTip = "防御系"),
	Support				UMETA(DisplayName = "サポート系",			ToolTip = "サポート系"),
	Counter				UMETA(DisplayName = "カウンター系",			ToolTip = "カウンター系"),

	Num				UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(CPPRpgActionType, CPPRpgActionType::Num)
