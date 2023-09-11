// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPCdEnemyType.generated.h"

/**
* 対象タイプ
*/
UENUM(BlueprintType)
enum class ECdEnemyType : uint8
{
	None			UMETA(DisplayName = "なし",		ToolTip = "なし"),
	Slime			UMETA(DisplayName = "スライム", ToolTip = "スライム"),
	Num				UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ECdEnemyType, ECdEnemyType::Num)

static FText ToText(ECdEnemyType Type)
{
	FString EnumName = TEXT("/Script/Project.ECdEnemyType");
	UEnum* const Enum = FindObject<UEnum>(nullptr, *EnumName);
	FString EnumNameString = Enum->GetNameStringByIndex(static_cast<int32>(Type));
	return FText::FromString(EnumNameString);
}

static FString ToString(ECdEnemyType Type)
{
	FText Text = ToText(Type);
	return Text.ToString();
}
