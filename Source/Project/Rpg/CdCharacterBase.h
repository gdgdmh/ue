// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "RpgBattleCharacterParameter.h"

#include "CdCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UCdCharacterBase : public UObject
{
	GENERATED_BODY()
	
public:
	UCdCharacterBase(const FObjectInitializer& ObjectInitializer);


	void SetParameter(const URpgBattleCharacterParameter& Parameter);

	TObjectPtr<URpgBattleCharacterParameter> GetParameter() const
	{
		return BattleCharactaerParameter;
	}

	void Damage(int32 AttackDamage);

	void OutputLog();

public:
	// 今は昔のシステムを使っておく
	UPROPERTY(EditAnywhere)
		TObjectPtr<URpgBattleCharacterParameter> BattleCharactaerParameter;

};
