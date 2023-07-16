// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPRpgBattleStatusType.generated.h"

/**
* 戦闘中ステータス
*/
UENUM(BlueprintType)
enum class ERpgBattleStatusType : uint8
{
	None			UMETA(DisplayName = "なし",		ToolTip = "なし"),
	Poisoned		UMETA(DisplayName = "毒",	ToolTip = "毒"),
	Paralyzed		UMETA(DisplayName = "麻痺", ToolTip = "麻痺"),
	Confused		UMETA(DisplayName = "混乱", ToolTip = "混乱"),
	Asleep			UMETA(DisplayName = "睡眠", ToolTip = "睡眠"),
	Blind			UMETA(DisplayName = "盲目", ToolTip = "盲目"),
	Stunned			UMETA(DisplayName = "気絶", ToolTip = "気絶"),
	Charmed			UMETA(DisplayName = "魅了", ToolTip = "魅了"),
	Silenced		UMETA(DisplayName = "沈黙", ToolTip = "沈黙"),
	Bleeding		UMETA(DisplayName = "出血", ToolTip = "出血"),
	Stoned			UMETA(DisplayName = "石化", ToolTip = "石化"),
	Frozen			UMETA(DisplayName = "凍結", ToolTip = "凍結"),
	Burning			UMETA(DisplayName = "炎上", ToolTip = "炎上"),
	Berserk			UMETA(DisplayName = "狂化", ToolTip = "狂化"),
	Taunted			UMETA(DisplayName = "挑発", ToolTip = "挑発"),

	Dead			UMETA(DisplayName = "死亡", ToolTip = "死亡"),
	Num				UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ERpgBattleStatusType, ERpgBattleStatusType::Num)
