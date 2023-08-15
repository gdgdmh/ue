// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePartyManager.h"

void UBattlePartyManager::Initialize()
{
	AllyParty.Reset();
	EnemyParty.Reset();
}

void UBattlePartyManager::SetParty(TWeakObjectPtr<UBattlePartySide> Party)
{
	if (!Party.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Party Data Invalid"));
		return;
	}

	ESideType Type = Party.Get()->GetType();
	if (Type == ESideType::Ally)
	{
		AllyParty = Party;
		return;
	}
	else if (Type == ESideType::Enemy)
	{
		EnemyParty = Party;
		return;
	}
	// ハンドリングされてないタイプ(新規追加をしたけど処理が書かれてない)
	UE_LOG(LogTemp, Log, TEXT("Type Invalid"));
	check(false);
}

TWeakObjectPtr<UBattlePartySide> UBattlePartyManager::Get(ESideType Type)
{
	if (Type == ESideType::Ally)
	{
		check(AllyParty.Get()->GetType() == ESideType::Ally); // 念のためにTypeがおかしくないかチェック
		return AllyParty;
	}
	if (Type == ESideType::Enemy)
	{
		check(EnemyParty.Get()->GetType() == ESideType::Enemy);  // 念のためにTypeがおかしくないかチェック
		return EnemyParty;
	}
	UE_LOG(LogTemp, Log, TEXT("Type Invalid"));
	check(false);
	return nullptr;
}
