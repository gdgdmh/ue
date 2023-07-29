// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RpgBattleCharacter.h"
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

	void Add(const TWeakObjectPtr<URpgBattleCharacter>& Target);

	void Remove(const TWeakObjectPtr<URpgBattleCharacter>& Target);

	void Clear();

public:

	UPROPERTY()
		TArray<TWeakObjectPtr<URpgBattleCharacter> > Characters; // 複数のキャラクター
};
