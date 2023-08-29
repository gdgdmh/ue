// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "CdCharacterBase.h"

#include "CdBattleParty.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UCdBattleParty : public UObject
{
	GENERATED_BODY()
	
public:
	UCdBattleParty(const FObjectInitializer& ObjectInitializer);

	void Add(const TObjectPtr<UCdCharacterBase>& Target);

	void Remove(const TObjectPtr<UCdCharacterBase>& Target);

	void Clear();

	const TArray<TObjectPtr<UCdCharacterBase> > GetList() const
	{
		return Characters;
	}

	void OutputLog();

protected:
	UPROPERTY()
		TArray<TObjectPtr<UCdCharacterBase> > Characters; // 複数のキャラクター
};
