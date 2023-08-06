// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPSideType.generated.h"

/**
* パーティ生成タイプ
*/
UENUM(BlueprintType)
enum class ESideType : uint8
{
	Ally			UMETA(DisplayName = "味方",		ToolTip = "味方"),
	Enemy			UMETA(DisplayName = "敵",		ToolTip = "敵"),
	Num				UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ESideType, ESideType::Num)
