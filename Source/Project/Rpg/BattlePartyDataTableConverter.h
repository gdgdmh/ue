// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RpgBattleParty.h"
#include "BattlePartyDataTable.h"
#include "CPPSideType.h"
#include "BattlePartyDataTableConverter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBattlePartyDataTableConverter : public UObject
{
	GENERATED_BODY()

public:
	TObjectPtr<URpgBattleParty> Convert(const TArray<FBattlePartyDataTable>& BattlePartyDataTable, ESideType Type);
	
};
