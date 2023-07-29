// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattlePartyFactory.h"

URpgBattlePartyFactory::URpgBattlePartyFactory(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

TWeakObjectPtr<URpgBattleParty> URpgBattlePartyFactory::Create(ERpgBattlePartyFactoryType Type)
{
	TWeakObjectPtr<URpgBattleParty> Party = NewObject<URpgBattleParty>();
	if (Type == ERpgBattlePartyFactoryType::Normal)
	{

	}
	else if (Type == ERpgBattlePartyFactoryType::Test)
	{
		//TWeakObjectPtr<URpgBattleCharacter> Character = NewObject<URpgBattleParty>();

		//Party.Get()->Add();
	}
	else
	{
	}

	return Party;
}


