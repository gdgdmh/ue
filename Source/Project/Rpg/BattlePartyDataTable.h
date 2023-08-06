// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RpgBattleStatus.h"
#include "BattlePartyDataTable.generated.h"


/**
 * �p�[�e�B�f�[�^�e�[�u��
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
		InitializeStatus();
		Name = FText::FromString("");
	}

	void InitializeStatus()
	{
		if (Status.IsValid())
		{
			Status.Get()->Reset();
			return;
		}
		Status = NewObject<URpgBattleStatus>();
	}

	bool IsStatusValid()
	{
		if (Status.IsValid())
		{
			return true;
		}
		return false;
	}

	// ���݂�HP
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Hp;
	// �ő�HP
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MaxHp;
	// ���݂�SP
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Sp;
	// �ő�SP
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MaxSp;
	// �U��
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 AttackPower;

	// �h��
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 DefencePower;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TWeakObjectPtr<URpgBattleStatus> Status;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText Name;

};