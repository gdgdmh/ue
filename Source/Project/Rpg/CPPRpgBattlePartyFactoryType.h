// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPRpgBattlePartyFactoryType.generated.h"

/**
* パーティ生成タイプ
*/
UENUM(BlueprintType)
enum class EBattlePartyFactoryType : uint8
{
	Normal			UMETA(DisplayName = "通常",		ToolTip = "通常"),
	Test			UMETA(DisplayName = "テスト",	ToolTip = "テスト"),
	Num				UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EBattlePartyFactoryType, EBattlePartyFactoryType::Num)
