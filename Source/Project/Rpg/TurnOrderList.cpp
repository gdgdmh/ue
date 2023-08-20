// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnOrderList.h"


UTurnOrderList::UTurnOrderList(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UTurnOrderList::Add(TObjectPtr<URpgBattleCharacterBase> Character)
{
	OrderList.Add(Character);
}

void UTurnOrderList::Remove(TObjectPtr<URpgBattleCharacterBase> Character)
{
	OrderList.Remove(Character);
}

void UTurnOrderList::Clear()
{
	OrderList.Empty();
}

int32 UTurnOrderList::Size() const
{
	return OrderList.Num();
}

TObjectPtr<URpgBattleCharacterBase> UTurnOrderList::Get(int32 Index) const
{
	check((0 <= Index) && (Index < OrderList.Num())); // check index range
	return OrderList[Index];
}

int32 UTurnOrderList::GetIndex(TObjectPtr<URpgBattleCharacterBase> Character) const
{
	const int32 Num = OrderList.Num();
	if (Num <= 0)
	{
		// データが存在しない
		return -1;
	}

	int32 Index = 0;
	for (const TObjectPtr<URpgBattleCharacterBase> CharacterBase : OrderList)
	{
		if (CharacterBase == Character)
		{
			return Index;
		}
	}
	// 見つからなかった
	return -1;
}

void UTurnOrderList::PopFront()
{
	if (OrderList.IsEmpty())
	{
		// 空の場合は意味なし
		return;
	}
	// 先頭のデータだけ削除
	OrderList.RemoveAt(0);
}

void UTurnOrderList::Normalize()
{
	bool bLoop = true;
	while (bLoop)
	{
		// 正規化
		// キャラクターが不正な状態
		// キャラクターが死亡
		// などしていたらリストから削除
		// いちいちbreakしてチェックし直すのは削除後のループの扱いがわからないため念のため
		bool bIsTask = false;
		for (const auto Character : OrderList)
		{
			if (!Character)
			{
				OrderList.Remove(Character);
				bIsTask = true;
				break;
			}
			if (Character.Get()->GetParameter().Get()->IsDead())
			{
				OrderList.Remove(Character);
				bIsTask = true;
				break;
			}
		}
		if (!bIsTask)
		{
			// 一通り何もなかったら終了
			bLoop = false;
		}
	}
}

TObjectPtr<URpgBattleCharacterBase> UTurnOrderList::GetTopCharacter() const
{
	if (Size() <= 0)
	{
		return nullptr;
	}
	return Get(0);
}

void UTurnOrderList::OutputLog() const
{
	int32 Index = 0;
	for (const TObjectPtr<URpgBattleCharacterBase>& Character : OrderList)
	{
		if (!Character)
		{
			UE_LOG(LogTemp, Log, TEXT("[%d] Invalid"), Index);
			++Index;
			continue;
		}
		UE_LOG(LogTemp, Log, TEXT("[%d]"), Index);
		++Index;
		Character.Get()->OutputLog();
	}
}
