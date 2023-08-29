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
	None						UMETA(DisplayName = "なし",							ToolTip = "なし"),
	Initialize					UMETA(DisplayName = "初期化",						ToolTip = "初期化"),
	PreStart					UMETA(DisplayName = "開始前",						ToolTip = "開始前"),
	Start						UMETA(DisplayName = "開始",							ToolTip = "開始"),

	PrePlayerTurn				UMETA(DisplayName = "プレイヤーターン前",			ToolTip = "プレイヤーターン前"),
	PlayerSelectAction			UMETA(DisplayName = "プレイヤーアクション選択",		ToolTip = "プレイヤーアクション選択"),
	PlayerAction				UMETA(DisplayName = "プレイヤーアクション",			ToolTip = "プレイヤーアクション"),
	PlayerActionAfter			UMETA(DisplayName = "プレイヤーアクション後",		ToolTip = "プレイヤーアクション後"),
	PlayerTurnFinish			UMETA(DisplayName = "プレイヤーターン終了",			ToolTip = "プレイヤーターン終了"),

	PlayerTurnAfter				UMETA(DisplayName = "プレイヤーターン終了時処理",	ToolTip = "プレイヤーターン終了時処理"),
	PlayerTurnAfterFinish		UMETA(DisplayName = "プレイヤーターン終了時処理後",	ToolTip = "プレイヤーターン終了時処理後"),

	PreEnemyTurn				UMETA(DisplayName = "敵ターン前",					ToolTip = "敵ターン前"),
	PreEnemyAction				UMETA(DisplayName = "敵アクション前",					ToolTip = "敵アクション前"),
	EnemyAction					UMETA(DisplayName = "敵アクション",					ToolTip = "敵アクション"),
	EnemyActionAfter			UMETA(DisplayName = "敵アクション後",				ToolTip = "敵アクション後"),
	EnemyActionFinish			UMETA(DisplayName = "敵アクション終了",				ToolTip = "敵アクション終了"),

	EnemyTurnAfter				UMETA(DisplayName = "敵ターン終了時処理",			ToolTip = "敵ターン終了時処理"),
	EnemyTurnAfterFinish		UMETA(DisplayName = "敵ターン終了時処理後",			ToolTip = "敵ターン終了時処理後"),

	TurnPreFinish				UMETA(DisplayName = "ターン終了前",					ToolTip = "ターン終了前"),
	TurnFinish					UMETA(DisplayName = "ターン終了",					ToolTip = "ターン終了"),

	PreFinish					UMETA(DisplayName = "終了前",						ToolTip = "終了前"),
	Finish						UMETA(DisplayName = "終了",							ToolTip = "終了"),

	Num					UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ERpgBattleProcessState, ERpgBattleProcessState::Num)


FText ToText(ERpgBattleProcessState State)
{
	FString EnumName = TEXT("/Script/Project.ERpgBattleProcessState");
	UEnum* const Enum = FindObject<UEnum>(nullptr, *EnumName);
	FString EnumNameString = Enum->GetNameStringByIndex(static_cast<int32>(State));
	return FText::FromString(EnumNameString);
}

