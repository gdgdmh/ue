// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "CdCharacterBase.h"

#include "BattlePartyManager.h"
#include "CPPRpgBattleProcessState.h"
#include "RpgTurnManager.h"
#include "RpgBattleDamageCalculator.h"
#include "CPPRpgBattleCommandType.h"
#include "ActionCardList.h"
#include "ActionCardParameter.h"
#include "CdCharacterParameter.h"

#include "RpgBattleManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgBattleManager : public UObject
{
	GENERATED_BODY()

public:
		
public:
	URpgBattleManager(const FObjectInitializer& ObjectInitializer);

	void SetBattleParty(TObjectPtr<UBattlePartyManager> Party)
	{
		check(Party);
		BattleParty = Party;
	}

	void SetCardList(TObjectPtr<UActionCardList> List);

	bool LoadCardParameter();
	bool LoadDeckParameter();

	bool LoadCharacterParameter();

	// 今の所固定で生成する
	void SetPlayer();
	void SetEnemies();

	TArray<TObjectPtr<UCdCharacterBase> > GetEnemy() const;

	void SetDefaultCardList();

	void NormalizeTurnList();
	void SetTurn();
	void OutputTurnLog() const;
	bool IsTurnListEmpty() const;
	void ChangeTurn();

	bool CheckSideAnnihilation();

	// 現在のステータスを返す
	ERpgBattleProcessState GetState() const
	{
		return ProcessState;
	}

	// 次のステータスに進める
	bool NextState();

	// プレイヤーのターンを終了させる
	void EndPlayerTurn();

	// 選択したアクションを処理する
	void ActionProc();

	// 選択カードindexのリセット
	void ResetSelectCardIndex();

	bool IsSelectCard() const;

	// 敵の中で攻撃対象を取得する
	TObjectPtr<UCdCharacterBase> GetEnemyAttackTarget();

	// プレイヤーのアクション処理
	bool ProcessPlayerAction();
	// 敵のアクション処理
	bool ProcessEnemyAction();

	// 行動選択のログ出力
	void OutputSelectCommandLog();

protected:
	UPROPERTY()
		TObjectPtr<UBattlePartyManager> BattleParty;

	UPROPERTY()
		TObjectPtr<UCdCharacterBase> Player;

	UPROPERTY()
		TArray<TObjectPtr<UCdCharacterBase> > Enemies;

	UPROPERTY()
		TObjectPtr<URpgTurnManager> TurnManager;
	UPROPERTY()
		TObjectPtr<URpgBattleDamageCalculator> DamageCalc;
	ERpgBattleProcessState ProcessState;

	UPROPERTY()
		TObjectPtr<UActionCardList> CardList;

	// 行動選択
	// 構造体にまとめるかも
	ERpgBattleCommandType SelectCommand;
	UPROPERTY()
		TObjectPtr<URpgBattleCharacterBase> AttackCharacter;
	UPROPERTY()
		TObjectPtr<URpgBattleCharacterBase> AttackTargetCharacter;

	// パラメーター
	UPROPERTY()
		TObjectPtr<UActionCardParameter> ActionCardParameter;

	UPROPERTY()
		TObjectPtr<UCdCharacterParameter> CharacterParameter;

	// 行動選択
	UPROPERTY()
		int32 SelectCardIndex;
};
