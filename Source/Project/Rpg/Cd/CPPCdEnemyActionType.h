// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPCdEnemyActionType.generated.h"

/**
* 行動タイプ
*/
UENUM(BlueprintType)
enum class ECdEnemyActionType : uint8
{
	None				UMETA(DisplayName = "なし",					ToolTip = "なし"),
	Attack				UMETA(DisplayName = "攻撃系",				ToolTip = "攻撃系"),
	Defence				UMETA(DisplayName = "防御系",				ToolTip = "防御系"),
	Buff				UMETA(DisplayName = "バフ系",				ToolTip = "バフ系"),
	Debuff				UMETA(DisplayName = "デバフ系",				ToolTip = "デバフ系"),
	Unknown				UMETA(DisplayName = "不明",					ToolTip = "不明"),

	Num					UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ECdEnemyActionType, ECdEnemyActionType::Num)

static FText ToText(ECdEnemyActionType Type)
{
	FString EnumName = TEXT("/Script/Project.ECdEnemyActionType");
	UEnum* const Enum = FindObject<UEnum>(nullptr, *EnumName);
	FString EnumNameString = Enum->GetNameStringByIndex(static_cast<int32>(Type));
	return FText::FromString(EnumNameString);
}
