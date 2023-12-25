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
#include "Cd/CdEnemyAndEnemyActionAssociator.h"

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

	// 戦闘パーティ設定(敵、味方)
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
	bool LoadEnemyAndEnemyActionParameter();
	bool SetupEnemyAndEnemyActionAssociator();

	// 今の所固定で生成する
	void SetPlayer();
	void SetEnemies();

	TArray<TObjectPtr<UCdCharacterBase> > GetEnemy() const;
	TObjectPtr<UCdEnemyAndEnemyActionAssociator> GetEnemyActionAssociator() const;

	void SetDefaultCardList();

	void NormalizeTurnList();
	void SetTurn();
	void OutputTurnLog() const;
	bool IsTurnListEmpty() const;
	void ChangeTurn();

	bool CheckSideAnnihilation();
	// 防御値のリセット処理
	void ResetDefencePointPlayer();
	void ResetDefencePointEnemy();

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


	// delegate
	FRpgBattleManagerChangePlayerInfoDelegate& GetChangePlayerInfoDelegate();
	FRpgBattleManagerChangeEnemyInfoDelegate& GetChangeEnemyInfoDelegate();
	FRpgBattleMangerChangeProcessStateDelegate& GetChangeProcessStateDelegate();

	// 行動選択のログ出力
	void OutputSelectCommandLog();

protected:
	// 戦闘パーティ(敵、味方含み)
	UPROPERTY()
		TObjectPtr<UBattlePartyManager> BattleParty;

	// プレイヤー(このクラス内で生成)
	UPROPERTY()
		TObjectPtr<UCdCharacterBase> Player;

	// 敵全体
	UPROPERTY()
		TArray<TObjectPtr<UCdCharacterBase> > Enemies;

	// ターン管理
	UPROPERTY()
		TObjectPtr<URpgTurnManager> TurnManager;

	// ダメージ計算
	UPROPERTY()
		TObjectPtr<URpgBattleDamageCalculator> DamageCalc;

	// ステート管理
	UPROPERTY()
		ERpgBattleProcessState ProcessState;

	// カード一覧
	UPROPERTY()
		TObjectPtr<UActionCardList> CardList;

	// 行動選択
	// 構造体にまとめるかも
	UPROPERTY()
		ERpgBattleCommandType SelectCommand;

	// 攻撃するキャラ
	UPROPERTY()
		TObjectPtr<URpgBattleCharacterBase> AttackCharacter;

	// 攻撃対象のキャラ
	UPROPERTY()
		TObjectPtr<URpgBattleCharacterBase> AttackTargetCharacter;

	// 選択された敵
	UPROPERTY()
		TObjectPtr<UCdCharacterBase> AttackTargetEnemy;

	// カードパラメーター
	UPROPERTY()
		TObjectPtr<UActionCardParameter> ActionCardParameter;

	// キャラクターパラメーター
	UPROPERTY()
		TObjectPtr<UCdCharacterParameter> CharacterParameter;

	// 敵の行動パラメーター
	UPROPERTY()
		TObjectPtr<UEnemyActionParameter> EnemyActionParameter;

	// 敵と敵のアクション紐づけ
	UPROPERTY()
		TObjectPtr<UEnemyAndEnemyActionDataParameter> EnemyAndEnemyActionParameter;

	// 敵と敵のアクションの関連付け
	UPROPERTY()
		TObjectPtr<UCdEnemyAndEnemyActionAssociator> EnemyAndEnemyActionAssociator;

	// 行動選択
	UPROPERTY()
		int32 SelectCardIndex;

	// 対象を選択したか
	UPROPERTY()
		bool bSelectTarget;

	// 選択できる敵の数
	UPROPERTY()
		int32 SelectableEnemyNum;

	// delegate
	FRpgBattleManagerChangePlayerInfoDelegate ChangePlayerInfoDelegate;

	FRpgBattleManagerChangeEnemyInfoDelegate ChangeEnemyInfoDelegate;

	FRpgBattleMangerChangeProcessStateDelegate ChangeProcessStateDelegate;
};
