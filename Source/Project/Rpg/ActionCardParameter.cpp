// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionCardParameter.h"

UActionCardParameter::UActionCardParameter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UActionCardParameter::LoadDataTable(const FString& DataTableReferencePath)
{
	DataTables.Empty();

	TObjectPtr<UDataTable> DataTable = LoadObject<UDataTable>(nullptr, *DataTableReferencePath, nullptr, LOAD_None, nullptr);
	if (!DataTable)
	{
		UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::LoadDataTable load failure"));
		return false;
	}

	// データ取得
	TArray<FName> RowArray = DataTable->GetRowNames();
	if (RowArray.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::LoadDataTable DataTable empty"));
		return true;
	}

	for (const FName RowName : RowArray)
	{
		auto TempTable = DataTable->FindRow<FActionCardDataTable>(RowName, FString());
		if (!TempTable)
		{
			UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::LoadDataTable Row find failure(TableType?)"));
			continue;
		}
		DataTables.Add(*TempTable);
	}

	if (DataTables.IsEmpty())
	{
		// 何もデータが入らなかった FindRowで失敗した?
		UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::LoadDataTable DataTable add failure(empty)"));
		return false;
	}
	return true;
}
