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

// 敵の陣営の取得(陣営が3つ以上には対応してない)
static ESideType GetEnemySide(ESideType Type)
{
	if (Type == ESideType::Ally)
	{
		return ESideType::Enemy;
	}
	if (Type == ESideType::Enemy)
	{
		return ESideType::Ally;
	}
	// ハンドリングできてないパターンがあるかNumなどのパラメーターを指定した
	UE_LOG(LogTemp, Log, TEXT("ESideType Invalid"));
	check(false);
	return ESideType::Ally;
}
