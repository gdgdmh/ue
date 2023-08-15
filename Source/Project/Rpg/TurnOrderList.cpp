// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnOrderList.h"


UTurnOrderList::UTurnOrderList(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UTurnOrderList::Add(TWeakObjectPtr<URpgBattleCharacterBase> Character)
{
	OrderList.Add(Character);
}

void UTurnOrderList::Remove(TWeakObjectPtr<URpgBattleCharacterBase> Character)
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

const TWeakObjectPtr<URpgBattleCharacterBase> UTurnOrderList::Get(int32 Index) const
{
	check((0 <= Index) && (Index < OrderList.Num())); // check index range
	return OrderList[Index];
}

int32 UTurnOrderList::GetIndex(TWeakObjectPtr<URpgBattleCharacterBase> Character) const
{
	const int32 Num = OrderList.Num();
	if (Num <= 0)
	{
		// データが存在しない
		return -1;
	}

	int32 Index = 0;
	for (const TWeakObjectPtr<URpgBattleCharacterBase> CharacterBase : OrderList)
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

void UTurnOrderList::OutputLog() const
{
	int32 Index = 0;
	for (const TWeakObjectPtr<URpgBattleCharacterBase>& Character : OrderList)
	{
		if (!Character.IsValid())
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
