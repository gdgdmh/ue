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
	/// �ǂݍ��݃X�e�[�^�X
	/// </summary>
	enum class LoadStatus : int32
	{
		Success,
		FailureLoadObject,		// LoadObject�Ɏ��s(�����炭���t�@�����X�p�X���Ԉ���Ă���)
		FailureEmptyData,		// DataTable����(���s�����ɂ��Ă��邪�A��������ł͐����Ƃ��Ă���)
		FailureTableType,		// �e���v���[�g�Ɏw�肳�ꂽ�^�Ǝ��ۂ̃f�[�^�e�[�u���̕����قȂ��Ă���H
		Failure
	};
public:

	/// <summary>
	/// �e�[�u���ǂݍ���
	/// </summary>
	/// <typeparam name="T">�f�[�^��`�����\����</typeparam>
	/// <param name="Datas">�f�[�^���i�[����z��</param>
	/// <param name="DataTableReferencePath">�Ώۃf�[�^�e�[�u���̃��t�@�����X�p�X</param>
	/// <returns>�ǂݍ��݌���</returns>
	template<typename T>
	LoadStatus LoadDataTable(TArray<T>& Datas, const FString& DataTableReferencePath)
	{
		Datas.Empty();
		TObjectPtr<UDataTable> DataTable = LoadObject<UDataTable>(nullptr, *DataTableReferencePath, nullptr, LOAD_None, nullptr);
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

};
