// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RpgBattleStatus.h"
#include "RpgBattleCharacterParameter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgBattleCharacterParameter : public UObject
{
	GENERATED_BODY()
	
public:
	URpgBattleCharacterParameter(const FObjectInitializer& ObjectInitializer);

	void NormalizeHp();
	void NormalizeSp();

public:
	// 現在のHP
	UPROPERTY(BlueprintReadWrite)
		int32 Hp;
	// 最大HP
	UPROPERTY(BlueprintReadWrite)
		int32 MaxHp;
	// 現在のSP
	UPROPERTY(BlueprintReadWrite)
		int32 Sp;
	// 最大SP
	UPROPERTY(BlueprintReadWrite)
		int32 MaxSp;
	// 攻撃
	UPROPERTY(BlueprintReadWrite)
		int32 AttackPower;

	// 防御
	UPROPERTY(BlueprintReadWrite)
		int32 DefencePower;

	// ステータス
	UPROPERTY(EditAnywhere)
		TWeakObjectPtr<URpgBattleStatus> Status;

};
