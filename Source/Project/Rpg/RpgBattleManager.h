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
#include "Cd/EnemyActionParameter.h"

#include "RpgBattleManager.generated.h"

// Delegate
// プレイヤーの情報が変化したときのDelegate
DECLARE_DELEGATE(FRpgBattleManagerChangePlayerInfoDelegate)
// 敵の情報が変化したときのDelegate
DECLARE_DELEGATE(FRpgBattleManagerChangeEnemyInfoDelegate)
// ProcessStateが変化したときのDelegate
DECLARE_DELEGATE_OneParam(FRpgBattleMangerChangeProcessStateDelegate, ERpgBattleProcessState)

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

	bool LoadEnemyActionParameter();

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

	int32 GetPlayerHp() const;
	int32 GetPlayerMaxHp() const;

	// 次のステータスに進める
	bool NextState();

	// ProcessState設定()
	void SetProcessState(ERpgBattleProcessState State);

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

	// 敵ウィジェットが選択されたとき
	void OnClickEnemyInfo(TObjectPtr<UCdCharacterBase> Enemy, bool isSelect);

	// 敵の選択が可能なタイミングか
	bool IsEnableSelectEnemy() const;
	// 選択可能な敵の数を取得
	int32 GetSelectableEnemyNum() const;



	FRpgBattleManagerChangePlayerInfoDelegate& GetChangePlayerInfoDelegate();
	FRpgBattleManagerChangeEnemyInfoDelegate& GetChangeEnemyInfoDelegate();
	FRpgBattleMangerChangeProcessStateDelegate& GetChangeProcessStateDelegate();

	//ChangeProcessStateDelegate

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
	UPROPERTY()
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

	// 選択された敵
	UPROPERTY()
		TObjectPtr<UCdCharacterBase> AttackTargetEnemy;

	// パラメーター
	UPROPERTY()
		TObjectPtr<UActionCardParameter> ActionCardParameter;

	UPROPERTY()
		TObjectPtr<UCdCharacterParameter> CharacterParameter;

	UPROPERTY()
		TObjectPtr<UEnemyActionParameter> EnemyActionParameter;

	// 行動選択
	UPROPERTY()
		int32 SelectCardIndex;

	UPROPERTY()
		bool bSelectTarget;

	UPROPERTY()
		int32 SelectableEnemyNum;

	FRpgBattleManagerChangePlayerInfoDelegate ChangePlayerInfoDelegate;

	FRpgBattleManagerChangeEnemyInfoDelegate ChangeEnemyInfoDelegate;

	FRpgBattleMangerChangeProcessStateDelegate ChangeProcessStateDelegate;
};
