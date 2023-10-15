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

	void AA();

	/// <summary>
	/// テーブル読み込み
	/// </summary>
	/// <typeparam name="T">データ定義した構造体</typeparam>
	/// <param name="Datas">データを格納する配列</param>
	/// <param name="DataTableReferencePath">対象データテーブルのリファレンスパス</param>
	/// <returns>読み込み結果</returns>
	template<typename T>
	LoadStatus LoadDataTable(TArray<T>& Datas, const FString& DataTableReferencePath);

};
