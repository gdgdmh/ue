// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Engine/DataTable.h"

#include "CPPRpgActionCardType.h"
#include "ActionCardAttackParameter.h"
#include "ActionCardDefenceParameter.h"

#include "ActionCardParameter.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FActionCardDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FActionCardDataTable()
	{
		Type = ERpgActionCardType::None;
		AtkPrmAttackPower = 0;
		DfPrmDefenceParameter = 0;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ERpgActionCardType Type;

	// AttackParameter
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 AtkPrmAttackPower;
	// DefenceParameter
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 DfPrmDefenceParameter;
};

/**
 * 
 */
UCLASS()
class PROJECT_API UActionCardParameter : public UObject
{
	GENERATED_BODY()

public:
	UActionCardParameter(const FObjectInitializer& ObjectInitializer);

	bool LoadDataTable(const FString& DataTableReferencePath);

protected:
	UPROPERTY()
		TArray<FActionCardDataTable> DataTables;
};
