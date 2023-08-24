// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "TurnOrderList.h"
#include "RpgBattleParty.h"

#include "TurnOrderCalculator.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UTurnOrderCalculator : public UObject
{
	GENERATED_BODY()
	
public:
	TObjectPtr<UTurnOrderList> Calc(TObjectPtr<URpgBattleParty> EnemyParty);
};
