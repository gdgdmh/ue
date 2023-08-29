// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "CdCharacterBase.h"

#include "RpgBattleParty.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgBattleParty : public UObject
{
	GENERATED_BODY()
	
public:
	URpgBattleParty();
	URpgBattleParty(const FObjectInitializer& ObjectInitializer);

	void Add(const TObjectPtr<UCdCharacterBase>& Target);

	void Remove(const TObjectPtr<UCdCharacterBase>& Target);

	void Clear();

	const TArray<TObjectPtr<UCdCharacterBase> > GetList() const
	{
		return Characters;
	}


	void OutputLog();

public:

	UPROPERTY()
		TArray<TObjectPtr<UCdCharacterBase> > Characters; // 複数のキャラクター
};
