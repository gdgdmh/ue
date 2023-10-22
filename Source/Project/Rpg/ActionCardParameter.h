// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Engine/DataTable.h"

#include "CPPRpgActionCardType.h"
#include "ActionCard.h"
#include "ActionCardList.h"
#include "ActionCardAttackParameter.h"
#include "ActionCardDefenceParameter.h"

#include "CPPRpgActionCardType.h"

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
		ActionType = ERpgActionType::None;
		Type = ERpgActionCardType::None;
		AtkPrmAttackPower = 0;
		AtkPrmTargetType = ERpgTargetType::None;
		DfPrmDefencePower = 0;
	}

	ERpgActionType GetActionType() const { return ActionType; }
	ERpgActionCardType GetCardType() const { return Type; }
	int32 GetAtkPrmAttackPower() const { return AtkPrmAttackPower; }
	ERpgTargetType GetAtkPrmTargetType() const { return AtkPrmTargetType; }

	int32 GetDfPrmDefencePower() const { return DfPrmDefencePower; }

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ERpgActionType ActionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ERpgActionCardType Type;

	// AttackParameter
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 AtkPrmAttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ERpgTargetType AtkPrmTargetType;

	// DefenceParameter
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 DfPrmDefencePower;
};

USTRUCT()
struct FActionCardCreateParameter
{
	GENERATED_BODY()

private:
	static const int32 DEFAULT_ENHANCEMENT_LEVEL = 1;
public:
	FActionCardCreateParameter()
	{
		CardType = ERpgActionCardType::None;
		EnhancementLevel = DEFAULT_ENHANCEMENT_LEVEL;
	}

	void SetCardType(ERpgActionCardType Type)
	{
		CardType = Type;
	}

	void SetEnhancementLevel(int32 Level)
	{
		EnhancementLevel = Level;
	}

	ERpgActionCardType GetCardType() const { return CardType; }
	int32 GetEnhancementLevel() const { return EnhancementLevel; }

public:
	
protected:

	UPROPERTY()
		ERpgActionCardType CardType;
	// 強化レベル(1～)
	UPROPERTY()
		int32 EnhancementLevel;

	// 補正パラメーター

};

USTRUCT(BlueprintType)
struct FActionCardDeckDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FActionCardDeckDataTable()
	{
		ActionType = ERpgActionType::None;
		CardType = ERpgActionCardType::None;
		EnhancementLevel = 1;
	}

	ERpgActionType GetActionType() const { return ActionType; }
	ERpgActionCardType GetCardType() const { return CardType; }
	int32 GetEnhancementLevel() const { return EnhancementLevel; }

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ERpgActionType ActionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ERpgActionCardType CardType;

		// 強化レベル(1～)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EnhancementLevel;
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

	bool LoadCardDataTable(const FString& DataTableReferencePath);

	bool LoadDeckDataTable(const FString& DataTableReferencePath);

	TObjectPtr<UActionCard> Create(const FActionCardCreateParameter& Parameter);
	TObjectPtr<UActionCardList> CreateDefaultDeck();

	const FActionCardDataTable* GetCardDataTableData(ERpgActionCardType CardType) const;

protected:
	UPROPERTY()
		TArray<FActionCardDataTable> CardDataTables;

	UPROPERTY()
		TArray<FActionCardDeckDataTable> DeckDataTables;
};
