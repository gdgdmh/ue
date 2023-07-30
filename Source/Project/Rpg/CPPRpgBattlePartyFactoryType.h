// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPRpgBattlePartyFactoryType.generated.h"

/**
* パーティ生成タイプ
*/
UENUM(BlueprintType)
enum class ERpgBattlePartyFactoryType : uint8
{
	Normal			UMETA(DisplayName = "通常",		ToolTip = "通常"),
	Test			UMETA(DisplayName = "テスト",	ToolTip = "テスト"),
	TestEnemy		UMETA(DisplayName = "敵テスト", ToolTip = "敵テスト"),
	Num				UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ERpgBattlePartyFactoryType, ERpgBattlePartyFactoryType::Num)
