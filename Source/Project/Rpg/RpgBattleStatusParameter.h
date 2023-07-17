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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ERpgBattleStatusType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Parameter1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Parameter2;

};
