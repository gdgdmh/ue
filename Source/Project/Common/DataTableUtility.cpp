// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableUtility.h"

template<typename T>
DataTableUtility::LoadStatus DataTableUtility::LoadDataTable(TArray<T>& Datas, const FString& DataTableReferencePath)
{
	Datas.Empty();
	TObjectPtr<T> DataTable = LoadObject<T>(nullptr, *DataTableReferencePath, nullptr, LOAD_None, nullptr);
	if (!DataTable)
	{
		// パスが間違っている？
		return LoadStatus::FailureLoadObject;
	}

	// データ取得
	TArray<FName> RowArray = DataTable->GetRowNames();
	if (RowArray.IsEmpty())
	{
		// データテーブルにそもそもデータがない
		return LoadStatus::FailureEmptyData;
	}

	for (const FName RowName : RowArray)
	{
		auto TempTable = DataTable->FindRow<T>(RowName, FString());
		if (!TempTable)
		{
			// 型が異なっている？
			return LoadStatus::FailureTableType;
		}
		// データに追加
		Datas.Add(*TempTable);
	}
	// 1件以上データ追加できているので成功
	return LoadStatus::Success;
}

