// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableUtility.h"

void UDataTableUtility::AA()
{
}

template<typename T>
UDataTableUtility::LoadStatus UDataTableUtility::LoadDataTable(TArray<T>& Datas, const FString& DataTableReferencePath)
{
	Datas.Empty();
	TObjectPtr<UDataTableT> DataTable = LoadObject<UDataTable>(nullptr, *DataTableReferencePath, nullptr, LOAD_None, nullptr);
	if (!DataTable)
	{
		// �p�X���Ԉ���Ă���H
		return LoadStatus::FailureLoadObject;
	}

	// �f�[�^�擾
	TArray<FName> RowArray = DataTable->GetRowNames();
	if (RowArray.IsEmpty())
	{
		// �f�[�^�e�[�u���ɂ��������f�[�^���Ȃ�
		return LoadStatus::FailureEmptyData;
	}

	for (const FName RowName : RowArray)
	{
		auto TempTable = DataTable->FindRow<T>(RowName, FString());
		if (!TempTable)
		{
			// �^���قȂ��Ă���H
			return LoadStatus::FailureTableType;
		}
		// �f�[�^�ɒǉ�
		Datas.Add(*TempTable);
	}
	// 1���ȏ�f�[�^�ǉ��ł��Ă���̂Ő���
	return LoadStatus::Success;
}
