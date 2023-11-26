// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Engine/DataTable.h"

#include "CPPCdEnemyActionType.h"
#include "../CPPRpgTargetType.h"
#include "../CPPCdEnemyType.h"

#include "EnemyActionParameter.generated.h"

/**
 * 敵の行動データテーブル
 */
USTRUCT(BlueprintType)
struct FEnemyActionDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FEnemyActionDataTable()
	{
		EnemyActionType = ECdEnemyActionType::None;
		AtkPrmTargetType = ERpgTargetType::None;
		AtkPrmAttackPower = 0;
		DfPrmDefencePower = 0;
	}
public:
	int32 GetAttackPower() const { return AtkPrmAttackPower; }
	int32 GetDefencePower() const { return DfPrmDefencePower; }

public:

	// アクションのタイプ(攻撃、防御、デバフなど)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECdEnemyActionType EnemyActionType;
	// ターゲットタイプ(単一、ランダム、複数など)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERpgTargetType AtkPrmTargetType;

	// 攻撃パラメーターのパワー
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AtkPrmAttackPower;

	// 防御パラメーターのパワー
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DfPrmDefencePower;

};

/**
 * FEnemyActionDataTableを扱うクラス
 */
UCLASS()
class PROJECT_API UEnemyActionParameter : public UObject
{
	GENERATED_BODY()

private:
	static const FName LightAttackName;
	static const FName LightDefenceName;

public:
	UEnemyActionParameter(const FObjectInitializer& ObjectInitializer);

	bool LoadDataTable(const FString& DataTableReferencePath);

	void Test();

	const FEnemyActionDataTable& Get(int32 index) const;
	int32 Size() const;

	const FEnemyActionDataTable& GetSimpleAttack() const;
	const FEnemyActionDataTable& GetSimpleDefence() const;

protected:
	UPROPERTY()
	TArray<FEnemyActionDataTable> ActionDataTables;

	UPROPERTY()
		int32 LightAttackIndex;

	UPROPERTY()
		int32 LightDefenceIndex;
};


/// <summary>
/// 敵と敵のアクションを紐付けるデータテーブル
/// </summary>
USTRUCT(BlueprintType)
struct FEnemyAndEnemyActionDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FEnemyAndEnemyActionDataTable()
		: EnemyActionDatas()
		, EnemyType(ECdEnemyType::None)
	{
	}

public:
	const TArray<FEnemyActionDataTable>& GetDatas() const { return EnemyActionDatas; }
	ECdEnemyType GetEnemyType() const { return EnemyType; }

public:
	// 敵のアクションテーブル
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FEnemyActionDataTable> EnemyActionDatas;
	
	// 敵のタイプ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ECdEnemyType EnemyType;
};

/// <summary>
/// アクション紐づけデータテーブルの集合テーブル
/// </summary>
USTRUCT(BlueprintType)
struct FEnemyAndEnemyActionDataTables : public FTableRowBase
{
	GENERATED_BODY()

public:
	FEnemyAndEnemyActionDataTables()
		: EnemyAndEnemyActionDatas()
	{
	}

public:
	// 敵のアクション紐づけテーブルのテーブル
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FEnemyAndEnemyActionDataTable> EnemyAndEnemyActionDatas;
};

UCLASS()
class PROJECT_API UEnemyAndEnemyActionDataParameter : public UObject
{
	GENERATED_BODY()

public:
	UEnemyAndEnemyActionDataParameter(const FObjectInitializer& ObjectInitializer);

	bool LoadDataTable(const FString& DataTableReferencePath);

	//const FEnemyActionDataTable& Get(int32 index) const;
	int32 Size() const;

	// 特定の敵の行動データを取得する
	bool GetEnemyActionData(TArray<FEnemyAndEnemyActionDataTable>& Tables, ECdEnemyType Type) const;

	// 指定した敵のランダムな行動テーブルを取得する
	bool GetRandomEnemyActionData(FEnemyAndEnemyActionDataTable& Tables, ECdEnemyType Type) const;

	int32 GetRandomInt(int32 Min, int32 Max) const;

public:
	void Test();

	//const FEnemyActionDataTable& GetSimpleAttack() const;
	//const FEnemyActionDataTable& GetSimpleDefence() const;

protected:
	UPROPERTY()
	TArray<FEnemyAndEnemyActionDataTables> EnemyAndEnemyActionDataTables;

};

