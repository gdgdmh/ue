// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPRpgTargetType.generated.h"

/**
* 対象タイプ
*/
UENUM(BlueprintType)
enum class CPPRpgTargetType : uint8
{
	None			UMETA(DisplayName = "なし",		ToolTip = "なし"),
	Single			UMETA(DisplayName = "単体", ToolTip = "単体"),
	SingleRandom	UMETA(DisplayName = "ランダムな単体", ToolTip = "ランダムな単体"),
	Multi			UMETA(DisplayName = "複数", ToolTip = "複数"),
	MultiRandom		UMETA(DisplayName = "ランダムな複数体", ToolTip = "ランダムな複数体"),
	EnemyAll		UMETA(DisplayName = "敵全体", ToolTip = "敵全体"),
	Num				UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(CPPRpgTargetType, CPPRpgTargetType::Num)
