// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPRpgActionCardType.generated.h"

/**
* 行動タイプ
*/
UENUM(BlueprintType)
enum class ERpgActionCardType : uint8
{
	None				UMETA(DisplayName = "なし",					ToolTip = "なし"),
	Attack				UMETA(DisplayName = "ストライク",			ToolTip = "シンプルな攻撃"),
	Defence				UMETA(DisplayName = "防御",					ToolTip = "シンプルな防御"),

	Num				UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ERpgActionCardType, ERpgActionCardType::Num)
