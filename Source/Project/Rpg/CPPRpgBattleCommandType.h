// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPRpgBattleCommandType.generated.h"

/**
* 戦闘コマンドタイプ
*/
UENUM(BlueprintType)
enum class ERpgBattleCommandType : uint8
{
	None			UMETA(DisplayName = "",		ToolTip = ""),
	Attack			UMETA(DisplayName = "",		ToolTip = ""),
	Defence			UMETA(DisplayName = "",		ToolTip = ""),
	Num				UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ERpgBattleCommandType, ERpgBattleCommandType::Num)
