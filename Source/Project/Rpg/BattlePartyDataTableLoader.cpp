// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePartyDataTableLoader.h"

bool UBattlePartyDataTableLoader::Load(const FString& DataTableReferencePath, TArray<FBattlePartyDataTable>& Output)
{
	Output.Empty();

	TObjectPtr<UDataTable> DataTable = LoadObject<UDataTable>(nullptr, *DataTableReferencePath, nullptr, LOAD_None, nullptr);
	if (!DataTable)
	{
		UE_LOG(LogTemp, Log, TEXT("DataTable load failure"));
		return false;
	}
	UE_LOG(LogTemp, Log, TEXT("DataTable load success"));

	// データ取得
	TArray<FName> RowArray = DataTable->GetRowNames();
	if (RowArray.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("DataTable empty"));
		return true;
	}

	for (const FName RowName : RowArray)
	{
		auto TempTable = DataTable->FindRow<FBattlePartyDataTable>(RowName, FString());
		if (!TempTable)
		{
			UE_LOG(LogTemp, Log, TEXT("Row find failure(TableType?)"));
			continue;
		}
		// ステータスが不正な状態なら初期化
		if (!TempTable->IsStatusValid())
		{
			TempTable->InitializeStatus();
		}
		Output.Add(*TempTable);
	}

	if (Output.IsEmpty())
	{
		// 何もデータが入らなかった FindRowで失敗した?
		UE_LOG(LogTemp, Log, TEXT("DataTable add failure(empty)"));
		return false;
	}

	return true;
}