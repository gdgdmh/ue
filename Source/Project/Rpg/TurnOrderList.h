// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "CdCharacterBase.h"
//#include "RpgBattleCharacterBase.h"
#include "BattlePartySide.h"

#include "TurnOrderList.generated.h"

/**
 * ターン順序リスト
 */
UCLASS()
class PROJECT_API UTurnOrderList : public UObject
{
	GENERATED_BODY()
	
public:
	UTurnOrderList(const FObjectInitializer& ObjectInitializer);

	void Add(TObjectPtr<UCdCharacterBase> Character);
	void Remove(TObjectPtr<UCdCharacterBase> Character);
	void Clear();
	int32 Size() const;
	TObjectPtr<UCdCharacterBase> Get(int32 Index) const;
	int32 GetIndex(TObjectPtr<UCdCharacterBase> Character) const;

	void PopFront();
	void Normalize();
	TObjectPtr<UCdCharacterBase> GetTopCharacter() const;

	void OutputLog() const;

protected:
	UPROPERTY()
		TArray<TObjectPtr<UCdCharacterBase> > OrderList;
};
