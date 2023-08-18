// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPRpgBattleProcessState.generated.h"

/**
 * 
 */
 // 処理状態
UENUM(BlueprintType)
enum class ERpgBattleProcessState : uint8
{
	None				UMETA(DisplayName = "なし",					ToolTip = "なし"),
	Initialize			UMETA(DisplayName = "初期化",				ToolTip = "初期化"),
	PreStart			UMETA(DisplayName = "開始前",				ToolTip = "開始前"),
	Start				UMETA(DisplayName = "開始",					ToolTip = "開始"),

	TurnPreCalc			UMETA(DisplayName = "ターン計算前",			ToolTip = "ターン計算前"),
	TurnCalc			UMETA(DisplayName = "ターン計算",			ToolTip = "ターン計算"),
	TurnCalcFinish		UMETA(DisplayName = "ターン計算終了時",		ToolTip = "ターン計算終了時"),

	TurnPreStart		UMETA(DisplayName = "ターン開始前",			ToolTip = "ターン開始前"),
	TurnStart			UMETA(DisplayName = "ターン開始",			ToolTip = "ターン開始"),

	ActionSelectWait	UMETA(DisplayName = "アクション選択待ち",	ToolTip = "アクション選択待ち"),
	ActionProcess		UMETA(DisplayName = "アクション処理",		ToolTip = "アクション処理"),
	ActionProcessFinish	UMETA(DisplayName = "アクション処理終了時",	ToolTip = "アクション処理終了時"),

	TurnPreFinish		UMETA(DisplayName = "ターン終了前",			ToolTip = "ターン終了前"),
	TurnFinish			UMETA(DisplayName = "ターン終了",			ToolTip = "ターン終了"),

	PreFinish			UMETA(DisplayName = "終了前",				ToolTip = "終了前"),
	Finish				UMETA(DisplayName = "終了",					ToolTip = "終了"),

	Num					UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ERpgBattleProcessState, ERpgBattleProcessState::Num)


FText ToString(ERpgBattleProcessState State)
{
	// ただ出力するだけならこっちの方式のほうがいいかも
#if 0
	{
		FString EnumName = TEXT("ERpgBattleCommandType");
		UEnum* const Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName);
		FString CommandEnumName = Enum->GetNameStringByIndex(static_cast<int32>(SelectCommand));
		UE_LOG(LogTemp, Log, TEXT("Command:%s"), *CommandEnumName);
}

#endif

	if (State == ERpgBattleProcessState::None)
	{
		return FText::FromString(TEXT("None"));
	}
	if (State == ERpgBattleProcessState::Initialize)
	{
		return FText::FromString(TEXT("Initialize"));
	}
	if (State == ERpgBattleProcessState::PreStart)
	{
		return FText::FromString(TEXT("PreStart"));
	}
	if (State == ERpgBattleProcessState::Start)
	{
		return FText::FromString(TEXT("Start"));
	}
	if (State == ERpgBattleProcessState::TurnPreCalc)
	{
		return FText::FromString(TEXT("TurnPreCalc"));
	}
	if (State == ERpgBattleProcessState::TurnCalc)
	{
		return FText::FromString(TEXT("TurnCalc"));
	}
	if (State == ERpgBattleProcessState::TurnCalcFinish)
	{
		return FText::FromString(TEXT("TurnCalcFinish"));
	}
	if (State == ERpgBattleProcessState::TurnPreStart)
	{
		return FText::FromString(TEXT("TurnPreStart"));
	}
	if (State == ERpgBattleProcessState::TurnStart)
	{
		return FText::FromString(TEXT("TurnStart"));
	}
	if (State == ERpgBattleProcessState::ActionSelectWait)
	{
		return FText::FromString(TEXT("ActionSelectWait"));
	}
	if (State == ERpgBattleProcessState::ActionProcess)
	{
		return FText::FromString(TEXT("ActionProcess"));
	}
	if (State == ERpgBattleProcessState::ActionProcessFinish)
	{
		return FText::FromString(TEXT("ActionProcessFinish"));
	}
	if (State == ERpgBattleProcessState::TurnPreFinish)
	{
		return FText::FromString(TEXT("TurnPreFinish"));
	}
	if (State == ERpgBattleProcessState::TurnFinish)
	{
		return FText::FromString(TEXT("TurnFinish"));
	}
	if (State == ERpgBattleProcessState::PreFinish)
	{
		return FText::FromString(TEXT("PreFinish"));
	}
	if (State == ERpgBattleProcessState::Finish)
	{
		return FText::FromString(TEXT("Finish"));
	}
	UE_LOG(LogTemp, Log, TEXT("State Not Match"));
	check(false);
	return FText::FromString(TEXT(""));
}

