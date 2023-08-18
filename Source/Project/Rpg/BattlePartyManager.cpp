// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePartyManager.h"

UBattlePartyManager::UBattlePartyManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, AllyParty(nullptr)
	, EnemyParty(nullptr)
{
}

void UBattlePartyManager::Initialize()
{
	AllyParty = nullptr;
	EnemyParty = nullptr;
}

void UBattlePartyManager::SetParty(TObjectPtr<UBattlePartySide> Party)
{
	if (!Party)
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

TObjectPtr<UBattlePartySide> UBattlePartyManager::Get(ESideType Type)
{
	check(AllyParty);
	check(EnemyParty);
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

// ノンターゲットで攻撃する際に攻撃対象とするキャラクターを取得
TObjectPtr<URpgBattleCharacterBase> UBattlePartyManager::GetAttackTarget(ESideType Type)
{
	// 対象のパーティ
	TObjectPtr<UBattlePartySide> Party = nullptr;
	if (Type == ESideType::Ally)
	{
		Party = AllyParty;
	}
	if (Type == ESideType::Enemy)
	{
		Party = EnemyParty;
	}
	if (Party == nullptr)
	{
		// Typeのハンドリング未定義
		UE_LOG(LogTemp, Log, TEXT("ESideType Invalid"));
		check(false);
		return nullptr;
	}

	if (!Party)
	{
		return nullptr;
	}
	if (Party.Get()->Get().Get()->GetList().IsEmpty())
	{
		return nullptr;
	}

	// 先頭から対象を選出
	TArray<TObjectPtr<URpgBattleCharacterBase> > List = Party.Get()->Get().Get()->GetList();
	for (TObjectPtr<URpgBattleCharacterBase> CharacterBase : List)
	{
		if (!CharacterBase)
		{
			continue;
		}
		// 死亡でなければ確定
		if (CharacterBase.Get()->GetParameter().Get()->IsDead())
		{
			continue;			
		}
		return CharacterBase;
	}
	UE_LOG(LogTemp, Log, TEXT("Type Invalid"));
	check(false);
	return nullptr;
}

ESideType UBattlePartyManager::GetSideType(const TObjectPtr<URpgBattleCharacterBase> CharacterBase) const
{
	check(CharacterBase);

	for (const TObjectPtr<URpgBattleCharacterBase> Character : AllyParty.Get()->Get().Get()->GetList())
	{
		if (CharacterBase == Character)
		{
			return ESideType::Ally;
		}
	}
	for (const TObjectPtr<URpgBattleCharacterBase> Character : EnemyParty.Get()->Get().Get()->GetList())
	{
		if (CharacterBase == Character)
		{
			return ESideType::Enemy;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("UBattlePartyManager::GetSideType Not Found"));
	check(false);
	return ESideType::Ally;
}
