// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RpgBattleCharacterBase.h"
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

	void Add(const TObjectPtr<URpgBattleCharacterBase>& Target);

	void Remove(const TObjectPtr<URpgBattleCharacterBase>& Target);

	void Clear();

	const TArray<TObjectPtr<URpgBattleCharacterBase> > GetList() const
	{
		return Characters;
	}


	void OutputLog();

public:

	UPROPERTY()
		TArray<TObjectPtr<URpgBattleCharacterBase> > Characters; // 複数のキャラクター
};
