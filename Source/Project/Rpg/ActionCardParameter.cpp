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

TObjectPtr<UActionCard> UActionCardParameter::Create(const FActionCardCreateParameter& Parameter)
{
	const ERpgActionCardType Type = Parameter.GetType();
	const int32 EnhancementLevel = Parameter.GetEnhancementLevel();
	// パラメーター正常性チェック
	if (Type == ERpgActionCardType::None)
	{
		UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::Create Type Invalid"));
		return nullptr;
	}
	if (EnhancementLevel <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::Create EnhancementLevel Invalid"));
		return nullptr;
	}

	const FActionCardDataTable* Data = GetCardDataTableData(Parameter.GetType());
	if (!Data)
	{
		UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::Create CardData Not Found"));
		return nullptr;
	}

	TObjectPtr<UActionCard> Card = NewObject<UActionCard>();

	if (Type == ERpgActionCardType::Attack)
	{
		Card.Get()->SetActionType(Data->GetActionType());
		Card.Get()->SetAttackTarget(Data->GetAtkPrmTargetType());
		Card.Get()->SetAttackPower(Data->GetAtkPrmAttackPower());
		return Card;
	}
	if (Type == ERpgActionCardType::Defence)
	{
		Card.Get()->SetActionType(Data->GetActionType());
		Card.Get()->SetDefenceTarget(ERpgTargetType::Single); // 必要なさそう
		Card.Get()->SetDefencePower(Data->GetDfPrmDefencePower());
		return Card;
	}

	// 不正なタイプ指定
	if (Type == ERpgActionCardType::None)
	{
		check(false);
		UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::Create ActionCardType InvalidType(None)"));
		return nullptr;
	}
	if (Type == ERpgActionCardType::Num)
	{
		check(false);
		UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::Create ActionCardType InvalidType(Num)"));
		return nullptr;
	}
	// 定義漏れ
	check(false);
	UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::Create ActionCardType NotHit"));
	return nullptr;
}

const FActionCardDataTable* UActionCardParameter::GetCardDataTableData(ERpgActionCardType CardType) const
{
	const int32 Size = DataTables.Num();
	for (int32 i = 0; i < Size; ++i)
	{
		const FActionCardDataTable& Data = DataTables[i];
		if (Data.Type == CardType)
		{
			return &Data;
		}
	}
	return nullptr;
}