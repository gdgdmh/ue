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
	bool Set(TObjectPtr<URpgBattleParty> AllyParty, TObjectPtr<URpgBattleParty> EnemyParty);

	TObjectPtr<UTurnOrderList> GetTurnOrderList();
	TObjectPtr<URpgBattleCharacterBase> GetCurrentTurnCharacter() const;


	void OutputLog() const;

private:
	UPROPERTY()
		TObjectPtr<UTurnOrderList> List;
	UPROPERTY()
		TObjectPtr<UTurnOrderCalculator> Calculator;
};
