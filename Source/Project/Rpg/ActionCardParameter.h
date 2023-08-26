// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPRpgActionCardType.h"

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

	UPROPERTY()
		ERpgActionCardType Type;



	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//ERpgBattleStatusType Type;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//int32 Parameter1;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//int32 Parameter2;
};


/**
 * 
 */
class PROJECT_API ActionCardParameter
{
public:
	ActionCardParameter();
	~ActionCardParameter();
};
