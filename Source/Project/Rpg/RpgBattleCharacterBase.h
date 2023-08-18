// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RpgBattleCharacterParameter.h"
#include "RpgBattleCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgBattleCharacterBase : public UObject
{
	GENERATED_BODY()
	
public:
	URpgBattleCharacterBase(const FObjectInitializer& ObjectInitializer);

	void SetParameter(const URpgBattleCharacterParameter& Parameter);

	TWeakObjectPtr<URpgBattleCharacterParameter> GetParameter() const
	{
		return BattleCharactaerParameter;
	}

	void Damage(int32 AttackDamage);

	void OutputLog();

public:
	UPROPERTY(EditAnywhere)
		TWeakObjectPtr<URpgBattleCharacterParameter> BattleCharactaerParameter;
};
