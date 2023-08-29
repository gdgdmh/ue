// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "BattlePartySide.h"
#include "RpgBattleCharacterBase.h"

#include "BattlePartyManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBattlePartyManager : public UObject
{
	GENERATED_BODY()
	
public:
	UBattlePartyManager(const FObjectInitializer& ObjectInitializer);

	void Initialize();

	void SetParty(TObjectPtr<UBattlePartySide> Party);

	TObjectPtr<UBattlePartySide> Get(ESideType Type);

	// ノンターゲットで攻撃する際に攻撃対象とするキャラクターを取得
	TObjectPtr<URpgBattleCharacterBase> GetAttackTarget(ESideType Type);

	ESideType GetSideType(const TObjectPtr<URpgBattleCharacterBase> CharacterBase) const;
protected:
	UPROPERTY()
		TObjectPtr<UBattlePartySide> AllyParty;
	UPROPERTY()
		TObjectPtr<UBattlePartySide> EnemyParty;
};
