// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RpgBattleStatus.h"
#include "BattlePartyDataTable.h"
#include "CPPCdEnemyType.h"
#include "RpgBattleCharacterParameter.generated.h"

/**
 * 戦闘キャラパラメーター
 * 変更する際にはFBattlePartyDataTableも変更すること
 */
UCLASS()
class PROJECT_API URpgBattleCharacterParameter : public UObject
{
	GENERATED_BODY()
	
public:
	URpgBattleCharacterParameter(const FObjectInitializer& ObjectInitializer);

	void NormalizeHp();
	void NormalizeSp();

	void Copy(const URpgBattleCharacterParameter& Parameter);
	void Copy(const FBattlePartyDataTable& PartyDataTable);

	void SetHp(int32 CurrentHp, int32 Max);
	void SetSp(int32 CurrentSp, int32 Max);
	void SetAttackPower(int32 Power);
	void SetDefencePower(int32 Power);
	void SetAgility(int32 AgilityValue);
	void SetEnemyType(ECdEnemyType Type);

	void Damage(int32 AttackDamage);

	int32 GetHp() const { return Hp; }
	int32 GetMaxHp() const { return MaxHp; }
	int32 GetSp() const { return Sp; }
	int32 GetMaxSp() const { return MaxSp; }
	int32 GetAttackPower() const { return AttackPower; }
	int32 GetDefencePower() const { return DefencePower; }
	int32 GetAgility() const { return Agility; }
	URpgBattleStatus& GetStatus() const { return *Status; }
	FText GetName() const { return Name; }
	ECdEnemyType GetType() const { return EnemyType; }

	bool IsDead() const;

	void OutputLog();

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

	UPROPERTY(BlueprintReadWrite)
		int32 Agility;

	// ステータス
	UPROPERTY(EditAnywhere)
	TObjectPtr<URpgBattleStatus> Status;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ECdEnemyType EnemyType;
};
