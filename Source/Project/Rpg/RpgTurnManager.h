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
	URpgTurnManager(const FObjectInitializer& ObjectInitializer);
	
	void ResetTurnOrderList();
	bool Set(TWeakObjectPtr<URpgBattleParty> AllyParty, TWeakObjectPtr<URpgBattleParty> EnemyParty);

	TWeakObjectPtr<UTurnOrderList> GetTurnOrderList();
	TWeakObjectPtr<URpgBattleCharacterBase> GetCurrentTurnCharacter() const;


	void OutputLog() const;

private:
	TWeakObjectPtr<UTurnOrderList> List;
	TWeakObjectPtr<UTurnOrderCalculator> Calculator;
};
