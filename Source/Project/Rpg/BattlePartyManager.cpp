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

// ノンターゲットで攻撃する際に攻撃対象とするキャラクターを取得
TWeakObjectPtr<URpgBattleCharacterBase> UBattlePartyManager::GetAttackTarget(ESideType Type)
{
	// 対象のパーティ
	TWeakObjectPtr<UBattlePartySide> Party = nullptr;
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

	if (!Party.IsValid())
	{
		return nullptr;
	}
	if (Party.Get()->Get().Get()->GetList().IsEmpty())
	{
		return nullptr;
	}

	// 先頭から対象を選出
	TArray<TWeakObjectPtr<URpgBattleCharacterBase> > List = Party.Get()->Get().Get()->GetList();
	/*
	for (int32 i = 0; i < List.Num(); ++i)
	{
		if (!List[i].IsValid())
		{
			continue;
		}
		// 死亡でなければ確定
		if (List[i].Get()->GetParameter().Get()->IsDead())
		{
			continue;
		}
		return List[i];
	}
	*/
	for (TWeakObjectPtr<URpgBattleCharacterBase> CharacterBase : List)
	{
		if (!CharacterBase.IsValid())
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

ESideType UBattlePartyManager::GetSideType(const TWeakObjectPtr<URpgBattleCharacterBase> CharacterBase) const
{
	check(CharacterBase.IsValid());

	for (const TWeakObjectPtr<URpgBattleCharacterBase> Character : AllyParty.Get()->Get().Get()->GetList())
	{
		if (CharacterBase == Character)
		{
			return ESideType::Ally;
		}
	}
	for (const TWeakObjectPtr<URpgBattleCharacterBase> Character : EnemyParty.Get()->Get().Get()->GetList())
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
