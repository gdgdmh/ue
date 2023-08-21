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

TArray<TObjectPtr<UActionCard> > UActionCardList::GetList() const
{
	return Cards;
}


