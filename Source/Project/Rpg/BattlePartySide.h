// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "CPPSideType.h"
#include "RpgBattleParty.h"

#include "BattlePartySide.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBattlePartySide : public UObject
{
	GENERATED_BODY()
public:
	UBattlePartySide(const FObjectInitializer& ObjectInitializer);

	void SetParty(TObjectPtr<URpgBattleParty> Source)
	{
		Party = Source;
	}

	void SetType(ESideType Source)
	{
		Type = Source;
	}

	TObjectPtr<URpgBattleParty> Get()
	{
		return Party;
	}

	ESideType GetType() const
	{
		return Type;
	}

protected:
	UPROPERTY()
		TObjectPtr<URpgBattleParty> Party;
	ESideType Type;

};
