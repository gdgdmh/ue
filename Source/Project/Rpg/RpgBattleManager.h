// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "BattlePartyManager.h"
#include "CPPRpgBattleProcessState.h"
#include "RpgTurnManager.h"
#include "RpgBattleDamageCalculator.h"
#include "CPPRpgBattleCommandType.h"

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

	void NormalizeTurnList();
	void SetTurn();
	void OutputTurn() const;
	bool IsTurnListEmpty() const;
	void ChangeTurn();

	bool CheckSideAnnihilation();

	ESideType GetSideType(const TObjectPtr<URpgBattleCharacterBase>& CharacterBase) const;

	// 現在のステータスを返す
	ERpgBattleProcessState GetState() const
	{
		return ProcessState;
	}

	// 次のステータスに進める
	bool NextState();

	// 選択したアクションを処理する
	void ActionProc();

	// 行動選択のログ出力
	void OutputSelectCommandLog();

protected:
	UPROPERTY()
		TObjectPtr<UBattlePartyManager> BattleParty;
	UPROPERTY()
		TObjectPtr<URpgTurnManager> TurnManager;
	UPROPERTY()
		TObjectPtr<URpgBattleDamageCalculator> DamageCalc;
	ERpgBattleProcessState ProcessState;

	// 行動選択
	// 構造体にまとめるかも
	ERpgBattleCommandType SelectCommand;
	UPROPERTY()
		TObjectPtr<URpgBattleCharacterBase> AttackCharacter;
	UPROPERTY()
		TObjectPtr<URpgBattleCharacterBase> AttackTargetCharacter;

};
