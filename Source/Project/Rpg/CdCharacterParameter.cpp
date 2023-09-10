// Fill out your copyright notice in the Description page of Project Settings.


#include "CdCharacterParameter.h"


UCdCharacterParameter::UCdCharacterParameter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCdCharacterParameter::LoadPlayerDataTable(const FString& DataTableReferencePath)
{
	PlayerData.Empty();

	TObjectPtr<UDataTable> DataTable = LoadObject<UDataTable>(nullptr, *DataTableReferencePath, nullptr, LOAD_None, nullptr);
	if (!DataTable)
	{
		UE_LOG(LogTemp, Log, TEXT("UCdCharacterParameter::LoadPlayerDataTable load failure"));
		return false;
}

	// データ取得
	TArray<FName> RowArray = DataTable->GetRowNames();
	if (RowArray.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("UCdCharacterParameter::LoadPlayerDataTable DataTable empty"));
		return true;
	}

	for (const FName RowName : RowArray)
	{
		auto TempTable = DataTable->FindRow<FCdCharacterDataTable>(RowName, FString());
		if (!TempTable)
		{
			UE_LOG(LogTemp, Log, TEXT("UCdCharacterParameter::LoadPlayerDataTable Row find failure(TableType?)"));
			continue;
		}
		PlayerData.Add(*TempTable);
	}

	if (PlayerData.IsEmpty())
	{
		// 何もデータが入らなかった FindRowで失敗した?
		UE_LOG(LogTemp, Log, TEXT("UCdCharacterParameter::LoadPlayerDataTable DataTable add failure(empty)"));
		return false;
	}
	return true;
}

bool UCdCharacterParameter::LoadEnemyDataTable(const FString& DataTableReferencePath)
{
	EnemyData.Empty();

	TObjectPtr<UDataTable> DataTable = LoadObject<UDataTable>(nullptr, *DataTableReferencePath, nullptr, LOAD_None, nullptr);
	if (!DataTable)
	{
		UE_LOG(LogTemp, Log, TEXT("UCdCharacterParameter::LoadEnemyDataTable load failure"));
		return false;
	}

	// データ取得
	TArray<FName> RowArray = DataTable->GetRowNames();
	if (RowArray.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("UCdCharacterParameter::LoadEnemyDataTable DataTable empty"));
		return true;
	}

	for (const FName RowName : RowArray)
	{
		auto TempTable = DataTable->FindRow<FCdCharacterDataTable>(RowName, FString());
		if (!TempTable)
		{
			UE_LOG(LogTemp, Log, TEXT("UCdCharacterParameter::LoadEnemyDataTable Row find failure(TableType?)"));
			continue;
		}
		EnemyData.Add(*TempTable);
	}

	if (EnemyData.IsEmpty())
	{
		// 何もデータが入らなかった FindRowで失敗した?
		UE_LOG(LogTemp, Log, TEXT("UCdCharacterParameter::LoadEnemyDataTable DataTable add failure(empty)"));
		return false;
	}
	return true;
}

void UCdCharacterParameter::GetPlayer(TArray<TObjectPtr<UCdCharacterBase> >& Player) const
{
	check(!PlayerData.IsEmpty());

	Player.Empty();
	for (auto Character : PlayerData)
	{
		TObjectPtr<UCdCharacterBase> CharacterBase = NewObject<UCdCharacterBase>();
		CharacterBase.Get()->GetParameter().Get()->SetHp(Character.GetHp(), Character.GetMaxHp());
		CharacterBase.Get()->GetParameter().Get()->SetAttackPower(Character.GetAttackPower());
		CharacterBase.Get()->GetParameter().Get()->SetDefencePower(Character.GetDefencePower());
		CharacterBase.Get()->GetParameter().Get()->SetEnemyType(ECdEnemyType::None);
		Player.Add(CharacterBase);
	}
}

void UCdCharacterParameter::GetEnemy(TArray<TObjectPtr<UCdCharacterBase> >& Enemies) const
{
	check(!EnemyData.IsEmpty());

	Enemies.Empty();
	for (auto Character : EnemyData)
	{
		TObjectPtr<UCdCharacterBase> CharacterBase = NewObject<UCdCharacterBase>();
		CharacterBase.Get()->GetParameter().Get()->SetHp(Character.GetHp(), Character.GetMaxHp());
		CharacterBase.Get()->GetParameter().Get()->SetAttackPower(Character.GetAttackPower());
		CharacterBase.Get()->GetParameter().Get()->SetDefencePower(Character.GetDefencePower());
		CharacterBase.Get()->GetParameter().Get()->SetEnemyType(Character.GetEnemyType());
		Enemies.Add(CharacterBase);
	}
}
