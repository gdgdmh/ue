// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "BattlePartyManager.h"
#include "CPPRpgBattleProcessState.h"
#include "RpgTurnManager.h"

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

	void SetBattleParty(TWeakObjectPtr<UBattlePartyManager> Party)
	{
		check(Party.IsValid());
		BattleParty = Party;
	}

	void SetTurn();
	void OutputTurn() const;

	// 現在のステータスを返す
	ERpgBattleProcessState GetState() const
	{
		return ProcessState;
	}

	// 次のステータスに進める
	bool NextState();

protected:
	TWeakObjectPtr<UBattlePartyManager> BattleParty;

	TWeakObjectPtr<URpgTurnManager> TurnManager;

	ERpgBattleProcessState ProcessState;

	//URpgTurnManager
};
