// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "RpgBattleStatus.h"
#include "BattlePartyDataTableLoader.generated.h"

USTRUCT(BlueprintType)
struct FBattlePartyDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FBattlePartyDataTable()
	{
		Hp = 0;
		MaxHp = 0;
		Sp = 0;
		MaxSp = 0;
		AttackPower = 0;
		DefencePower = 0;
		Status = NewObject<URpgBattleStatus>();
		Name = FText::FromString("");
	}

	// åªç›ÇÃHP
	UPROPERTY(BlueprintReadWrite)
		int32 Hp;
	// ç≈ëÂHP
	UPROPERTY(BlueprintReadWrite)
		int32 MaxHp;
	// åªç›ÇÃSP
	UPROPERTY(BlueprintReadWrite)
		int32 Sp;
	// ç≈ëÂSP
	UPROPERTY(BlueprintReadWrite)
		int32 MaxSp;
	// çUåÇ
	UPROPERTY(BlueprintReadWrite)
		int32 AttackPower;

	// ñhå‰
	UPROPERTY(BlueprintReadWrite)
		int32 DefencePower;

	UPROPERTY(BlueprintReadWrite)
		TWeakObjectPtr<URpgBattleStatus> Status;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText Name;

};

/**
 * 
 */
UCLASS()
class PROJECT_API UBattlePartyDataTableLoader : public UObject
{
	GENERATED_BODY()
	
public:
	bool Load(const FString& FileName, TArray<FBattlePartyDataTable>& Output);
};
