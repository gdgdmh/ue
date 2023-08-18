// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RpgBattleStatus.h"
#include "BattlePartyDataTable.generated.h"


/**
 * パーティデータテーブル
 * 追加変更する際にはURpgBattleCharacterParameterも変更すること
 */
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
		Agility = 0;
		InitializeStatus();
		Name = FText::FromString("");
	}

	void InitializeStatus()
	{
		if (Status)
		{
			Status.Get()->Reset();
			return;
		}
		Status = NewObject<URpgBattleStatus>();
	}

	bool IsStatusValid()
	{
		if (Status)
		{
			return true;
		}
		return false;
	}

	// 現在のHP
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Hp;
	// 最大HP
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MaxHp;
	// 現在のSP
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Sp;
	// 最大SP
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MaxSp;
	// 攻撃
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 AttackPower;

	// 防御
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 DefencePower;

	// 素早さ
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Agility;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TObjectPtr<URpgBattleStatus> Status;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText Name;

};
