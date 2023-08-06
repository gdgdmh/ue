// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BattlePartyDataTable.h"
#include "BattlePartyDataTableLoader.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBattlePartyDataTableLoader : public UObject
{
	GENERATED_BODY()
	
public:
	// データテーブルをロードする
	bool Load(const FString& DataTableReferencePath, TArray<FBattlePartyDataTable>& Output);
};
