// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "BattlePartySide.h"

#include "BattlePartyManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBattlePartyManager : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize();

	void SetParty(TWeakObjectPtr<UBattlePartySide> Party);

	TWeakObjectPtr<UBattlePartySide> Get(ESideType Type);

	// ノンターゲットで攻撃する際に攻撃対象とするキャラクターを取得
	TWeakObjectPtr<URpgBattleCharacterBase> GetAttackTarget(ESideType Type);

	ESideType GetSideType(const TWeakObjectPtr<URpgBattleCharacterBase> CharacterBase) const;
public:
	TWeakObjectPtr<UBattlePartySide> AllyParty;
	TWeakObjectPtr<UBattlePartySide> EnemyParty;
};
