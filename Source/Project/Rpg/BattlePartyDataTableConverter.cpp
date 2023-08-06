// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePartyDataTableConverter.h"

#include "CharacterParameterConverter.h"

TWeakObjectPtr<URpgBattleParty> UBattlePartyDataTableConverter::Convert(const TArray<FBattlePartyDataTable>& BattlePartyDataTable, ESideType Type)
{
	TWeakObjectPtr<UCharacterParameterConverter> Converter = NewObject<UCharacterParameterConverter>();
	check(Converter != nullptr);

	TWeakObjectPtr<URpgBattleParty> Party = NewObject<URpgBattleParty>();

	for (const FBattlePartyDataTable& PartyData : BattlePartyDataTable)
	{
		TWeakObjectPtr<URpgBattleCharacterParameter> CharacterParameter = NewObject<URpgBattleCharacterParameter>();
		CharacterParameter.Get()->Copy(PartyData);
		TWeakObjectPtr<URpgBattleCharacterBase> CharacterBase = Converter.Get()->Convert(*CharacterParameter.Get(), Type);
		if (CharacterBase.IsValid())
		{
			Party.Get()->Add(CharacterBase);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("CharacterBase Convert Failure"));
			check(CharacterBase.IsValid());
		}
	}

	return Party;
}