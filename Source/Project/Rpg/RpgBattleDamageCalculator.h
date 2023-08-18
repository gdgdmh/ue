// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "CPPRpgBattleCommandType.h"
#include "RpgBattleCharacterBase.h"

#include "RpgBattleDamageCalculator.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgBattleDamageCalculator : public UObject
{
	GENERATED_BODY()
	
public:

	void Calc(int32& Damage, TObjectPtr<URpgBattleCharacterBase> Attacker, TObjectPtr<URpgBattleCharacterBase> Target, ERpgBattleCommandType CommandType);

	int32 CalcBaseDamage(int32 AttackPower, int32 DefencePower);
};
