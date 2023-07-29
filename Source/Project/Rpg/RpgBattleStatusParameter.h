// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPRpgBattleStatusType.h"
#include "RpgBattleStatusParameter.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FRpgBattleStatusParameter
{
	GENERATED_BODY()
public:
	FRpgBattleStatusParameter()
	{
		Type = ERpgBattleStatusType::None;
		Parameter1 = 0;
		Parameter2 = 0;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ERpgBattleStatusType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Parameter1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Parameter2;
};
