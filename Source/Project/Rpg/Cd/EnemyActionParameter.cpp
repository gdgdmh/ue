// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyActionParameter.h"

const FName UEnemyActionParameter::LightAttackName = TEXT("LightAttack");
const FName UEnemyActionParameter::LightDefenceName = TEXT("LightDefence");

UEnemyActionParameter::UEnemyActionParameter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ActionDataTables()
	, LightAttackIndex(-1)
	, LightDefenceIndex(-1)
{
}

bool UEnemyActionParameter::LoadDataTable(const FString& DataTableReferencePath)
{
	ActionDataTables.Empty();
	TObjectPtr<UDataTable> DataTable = LoadObject<UDataTable>(nullptr, *DataTableReferencePath, nullptr, LOAD_None, nullptr);
	if (!DataTable)
	{
		UE_LOG(LogTemp, Log, TEXT("UEnemyActionParameter::LoadDataTable load failure"));
		return false;
	}

	// データ取得
	TArray<FName> RowArray = DataTable->GetRowNames();
	if (RowArray.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("UEnemyActionParameter::LoadDataTable DataTable empty"));
		return true;
	}

	int32 index = 0;
	for (const FName RowName : RowArray)
	{
		auto TempTable = DataTable->FindRow<FEnemyActionDataTable>(RowName, FString());
		if (!TempTable)
		{
			UE_LOG(LogTemp, Log, TEXT("UEnemyActionParameter::LoadDataTable Row find failure(TableType?)"));
			continue;
		}

		if (LightAttackName == RowName)
		{
			// 名前が一致したらindexをとっておく
			LightAttackIndex = index;
		}
		else if (LightDefenceName == RowName)
		{
			LightDefenceIndex = index;
		}

		ActionDataTables.Add(*TempTable);
		++index;
	}

	if (ActionDataTables.IsEmpty())
	{
		// 何もデータが入らなかった FindRowで失敗した?
		UE_LOG(LogTemp, Log, TEXT("UEnemyActionParameter::LoadDataTable DataTable add failure(empty)"));
		return false;
	}
	if (LightAttackIndex < 0)
	{
		UE_LOG(LogTemp, Log, TEXT("UEnemyActionParameter::LoadDataTable LightAttackIndex Not Found"));
	}
	if (LightDefenceIndex < 0)
	{
		UE_LOG(LogTemp, Log, TEXT("UEnemyActionParameter::LoadDataTable LightDefenceIndex Not Found"));
	}
	return true;
}

const FEnemyActionDataTable& UEnemyActionParameter::Get(int32 index) const
{
	return ActionDataTables[index];
}

const FEnemyActionDataTable& UEnemyActionParameter::GetSimpleAttack() const
{
	checkf(LightAttackIndex >= 0, TEXT("UEnemyActionParameter::GetSimpleAttack Invalid"));
	return ActionDataTables[LightAttackIndex];
}

const FEnemyActionDataTable& UEnemyActionParameter::GetSimpleDefence() const
{
	checkf(LightDefenceIndex >= 0, TEXT("UEnemyActionParameter::GetSimpleDefence Invalid"));
	return ActionDataTables[LightDefenceIndex];
}


int32 UEnemyActionParameter::Size() const
{
	return ActionDataTables.Num();
}
