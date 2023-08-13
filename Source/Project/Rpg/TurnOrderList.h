// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "RpgBattleCharacterBase.h"

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

	void Add(TWeakObjectPtr<URpgBattleCharacterBase> Character);
	void Remove(TWeakObjectPtr<URpgBattleCharacterBase> Character);
	void Clear();
	int32 Size() const;
	const TWeakObjectPtr<URpgBattleCharacterBase> Get(int32 Index) const;
	int32 GetIndex(TWeakObjectPtr<URpgBattleCharacterBase> Character) const;

protected:
	TArray<TWeakObjectPtr<URpgBattleCharacterBase> > OrderList;
};
