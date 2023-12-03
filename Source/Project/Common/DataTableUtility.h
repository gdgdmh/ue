// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataTableUtility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UDataTableUtility : public UObject
{
	GENERATED_BODY()
	
public:
	/// <summary>
	/// 読み込みステータス
	/// </summary>
	enum class LoadStatus : int32
	{
		Success,
		FailureLoadObject,		// LoadObjectに失敗(おそらくリファレンスパスが間違っている)
		FailureEmptyData,		// DataTableが空(失敗扱いにしているが、実装次第では成功としても可)
		FailureTableType,		// テンプレートに指定された型と実際のデータテーブルの方が異なっている？
		Failure
	};
public:

	/// <summary>
	/// テーブル読み込み
	/// </summary>
	/// <typeparam name="T">データ定義した構造体</typeparam>
	/// <param name="Datas">データを格納する配列</param>
	/// <param name="DataTableReferencePath">対象データテーブルのリファレンスパス</param>
	/// <returns>読み込み結果</returns>
	template<typename T>
	LoadStatus LoadDataTable(TArray<T>& Datas, const FString& DataTableReferencePath)
	{
		Datas.Empty();
		TObjectPtr<UDataTable> DataTable = LoadObject<UDataTable>(nullptr, *DataTableReferencePath, nullptr, LOAD_None, nullptr);
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

};
