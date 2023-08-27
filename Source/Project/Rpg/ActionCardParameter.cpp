// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionCardParameter.h"

#include "ActionCardList.h"

UActionCardParameter::UActionCardParameter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UActionCardParameter::LoadCardDataTable(const FString& DataTableReferencePath)
{
	CardDataTables.Empty();

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
		CardDataTables.Add(*TempTable);
	}

	if (CardDataTables.IsEmpty())
	{
		// 何もデータが入らなかった FindRowで失敗した?
		UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::LoadDataTable DataTable add failure(empty)"));
		return false;
	}
	return true;
}

bool UActionCardParameter::LoadDeckDataTable(const FString& DataTableReferencePath)
{
	DeckDataTables.Empty();

	TObjectPtr<UDataTable> DataTable = LoadObject<UDataTable>(nullptr, *DataTableReferencePath, nullptr, LOAD_None, nullptr);
	if (!DataTable)
	{
		UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::LoadDeckDataTable load failure"));
		return false;
	}

	// データ取得
	TArray<FName> RowArray = DataTable->GetRowNames();
	if (RowArray.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::LoadDeckDataTable DataTable empty"));
		return true;
	}

	for (const FName RowName : RowArray)
	{
		auto TempTable = DataTable->FindRow<FActionCardDeckDataTable>(RowName, FString());
		if (!TempTable)
		{
			UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::LoadDeckDataTable Row find failure(TableType?)"));
			continue;
		}
		DeckDataTables.Add(*TempTable);
	}

	if (DeckDataTables.IsEmpty())
	{
		// 何もデータが入らなかった FindRowで失敗した?
		UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::LoadDeckDataTable DataTable add failure(empty)"));
		return false;
	}
	return true;
}

TObjectPtr<UActionCard> UActionCardParameter::Create(const FActionCardCreateParameter& Parameter)
{
	const ERpgActionCardType Type = Parameter.GetCardType();
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

	const FActionCardDataTable* Data = GetCardDataTableData(Parameter.GetCardType());
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

TObjectPtr<UActionCardList> UActionCardParameter::CreateDefaultDeck()
{
	if (DeckDataTables.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::CreateDefaultDeck empty"));
		return nullptr;
	}

	TObjectPtr<UActionCardList> List = NewObject<UActionCardList>();
	for (auto Data : DeckDataTables)
	{
		FActionCardCreateParameter Parameter;
		Parameter.SetCardType(Data.GetCardType());
		Parameter.SetEnhancementLevel(Data.GetEnhancementLevel());

		TObjectPtr<UActionCard> Card = Create(Parameter);
		if (Card)
		{
			List.Get()->AddCard(Card);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("UActionCardParameter::CreateDefaultDeck create card failure"));
			return nullptr;
		}
	}
	return List;
}

const FActionCardDataTable* UActionCardParameter::GetCardDataTableData(ERpgActionCardType CardType) const
{
	const int32 Size = CardDataTables.Num();
	for (int32 i = 0; i < Size; ++i)
	{
		const FActionCardDataTable& Data = CardDataTables[i];
		if (Data.Type == CardType)
		{
			return &Data;
		}
	}
	return nullptr;
}