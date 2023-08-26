// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPRpgActionCardType.h"

#include "ActionCardParameter.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FActionCardDataTable
{
	GENERATED_BODY()

public:
	FActionCardDataTable()
	{
		Type = ERpgActionCardType::None;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ERpgActionCardType Type;
};

/**
 * 
 */
UCLASS()
class PROJECT_API UActionCardParameter : public UObject
{
	GENERATED_BODY()

public:
};
