// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Engine/DataTable.h"

#include "CPPCdEnemyActionType.h"
#include "../CPPRpgTargetType.h"


#include "EnemyActionParameter.generated.h"

/**
 *
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
 *
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
