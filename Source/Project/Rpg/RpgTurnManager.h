// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "TurnOrderList.h"
#include "TurnOrderCalculator.h"

#include "RpgTurnManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgTurnManager : public UObject
{
	GENERATED_BODY()
	
public:
	static const int32 DEFAULT_TURN = 1;
public:
	URpgTurnManager(const FObjectInitializer& ObjectInitializer);
	
	void ResetTurnOrderList();
	bool Set(TObjectPtr<URpgBattleParty> AllyParty, TObjectPtr<URpgBattleParty> EnemyParty);
	void PopFront();
	void Normalize();

	TObjectPtr<UTurnOrderList> GetTurnOrderList();
	TObjectPtr<URpgBattleCharacterBase> GetCurrentTurnCharacter() const;

	bool IsTurnListEmpty() const;

	void OutputLog() const;

private:
	UPROPERTY()
		TObjectPtr<UTurnOrderList> List;
	UPROPERTY()
		TObjectPtr<UTurnOrderCalculator> Calculator;

	int32 TurnCount;
};
