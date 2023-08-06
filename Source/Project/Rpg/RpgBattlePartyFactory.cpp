// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattlePartyFactory.h"
#include "RpgBattleCharacterParameter.h"
#include "CharacterParameterConverter.h"

URpgBattlePartyFactory::URpgBattlePartyFactory(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

TWeakObjectPtr<URpgBattleParty> URpgBattlePartyFactory::Create(ERpgBattlePartyFactoryType Type)
{
	TWeakObjectPtr<URpgBattleParty> Party = NewObject<URpgBattleParty>();
	TWeakObjectPtr<UCharacterParameterConverter> Converter = NewObject<UCharacterParameterConverter>();
	if (Type == ERpgBattlePartyFactoryType::Normal)
	{
		// 現在は未定義
	}
	else if (Type == ERpgBattlePartyFactoryType::Test)
	{
		{
			TWeakObjectPtr<URpgBattleCharacterParameter> Parameter = NewObject<URpgBattleCharacterParameter>();
			Parameter.Get()->SetHp(10, 10);
			Parameter.Get()->SetSp(0, 0);
			Parameter.Get()->SetAttackPower(5);
			Parameter.Get()->SetDefencePower(7);
			Parameter.Get()->OutputLog();
			TWeakObjectPtr<URpgBattleCharacterBase> CharacterBase = Converter.Get()->Convert(*Parameter.Get(), ESideType::Ally);
			Party.Get()->Add(CharacterBase);
			Party.Get()->OutputLog();
		}
	}
	else if (Type == ERpgBattlePartyFactoryType::TestEnemy)
	{
		{
			TWeakObjectPtr<URpgBattleCharacterParameter> Parameter = NewObject<URpgBattleCharacterParameter>();
			Parameter.Get()->SetHp(9, 9);
			Parameter.Get()->SetSp(1, 1);
			Parameter.Get()->SetAttackPower(3);
			Parameter.Get()->SetDefencePower(5);
			Parameter.Get()->OutputLog();
			TWeakObjectPtr<URpgBattleCharacterBase> CharacterBase = Converter.Get()->Convert(*Parameter.Get(), ESideType::Enemy);
			CharacterBase->OutputLog();
			Party.Get()->Add(CharacterBase);
			Party.Get()->OutputLog();
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("URpgBattlePartyFactory::Create UnknownType"));
		check(false);
	}

	return Party;
}


