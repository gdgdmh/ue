// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RpgBattleCharacterParameter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgBattleCharacterParameter : public UObject
{
	GENERATED_BODY()
	
public:
	URpgBattleCharacterParameter();

	void NormalizeHp();
	void NormalizeSp();

public:
	UPROPERTY(BlueprintReadWrite)
		int32 Hp;

	UPROPERTY(BlueprintReadWrite)
		int32 MaxHp;

	UPROPERTY(BlueprintReadWrite)
		int32 Sp;

	UPROPERTY(BlueprintReadWrite)
		int32 MaxSp;

};
