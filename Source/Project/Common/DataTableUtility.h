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

	void AA();

	/// <summary>
	/// �e�[�u���ǂݍ���
	/// </summary>
	/// <typeparam name="T">�f�[�^��`�����\����</typeparam>
	/// <param name="Datas">�f�[�^���i�[����z��</param>
	/// <param name="DataTableReferencePath">�Ώۃf�[�^�e�[�u���̃��t�@�����X�p�X</param>
	/// <returns>�ǂݍ��݌���</returns>
	template<typename T>
	LoadStatus LoadDataTable(TArray<T>& Datas, const FString& DataTableReferencePath);

};
