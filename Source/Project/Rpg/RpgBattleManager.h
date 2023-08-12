// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "BattlePartyManager.h"
#include "CPPRpgBattleProcessState.h"

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

	void SetBattleParty(TWeakObjectPtr<UBattlePartyManager>&& Party)
	{
		PartyManager = Party;
	}

	// 現在のステータスを返す
	ERpgBattleProcessState GetState() const
	{
		return ProcessState;
	}

	// 次のステータスに進める
	bool NextState();

protected:
	TWeakObjectPtr<UBattlePartyManager> PartyManager;
	ERpgBattleProcessState ProcessState;
};
