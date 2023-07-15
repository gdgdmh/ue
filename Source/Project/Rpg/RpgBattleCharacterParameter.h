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

public:
	UPROPERTY(BlueprintReadWrite)
		int32 Hp;

	UPROPERTY(BlueprintReadWrite)
		int32 Sp;


};
