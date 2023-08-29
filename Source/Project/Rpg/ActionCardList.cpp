// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionCardList.h"

UActionCardList::UActionCardList(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UActionCardList::AddCard(TObjectPtr<UActionCard> Card)
{
	Cards.Add(Card);
}

void UActionCardList::RemoveCard(TObjectPtr<UActionCard> Card)
{
	Cards.Remove(Card);
}

void UActionCardList::CopyCard(UActionCardList& Source)
{
	Cards.Empty();
	for (auto Card : Source.Cards)
	{
		Cards.Add(Card);
	}
}

int32 UActionCardList::GetSize() const
{
	return Cards.Num();
}

TObjectPtr<UActionCard> UActionCardList::GetCard(int32 Index)
{
	check((0 <= Index) && (Index < Cards.Num()));
	return Cards[Index];
}

TArray<TObjectPtr<UActionCard> > UActionCardList::GetList() const
{
	return Cards;
}


