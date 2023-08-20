// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePartyDataTableConverter.h"

#include "CharacterParameterConverter.h"

TObjectPtr<URpgBattleParty> UBattlePartyDataTableConverter::Convert(const TArray<FBattlePartyDataTable>& BattlePartyDataTable, ESideType Type)
{
	TObjectPtr<UCharacterParameterConverter> Converter = NewObject<UCharacterParameterConverter>();
	check(Converter != nullptr);

	TObjectPtr<URpgBattleParty> Party = NewObject<URpgBattleParty>();

	for (const FBattlePartyDataTable& PartyData : BattlePartyDataTable)
	{
		TObjectPtr<URpgBattleCharacterParameter> CharacterParameter = NewObject<URpgBattleCharacterParameter>();
		CharacterParameter.Get()->Copy(PartyData);
		TObjectPtr<URpgBattleCharacterBase> CharacterBase = Converter.Get()->Convert(*CharacterParameter.Get(), Type);
		if (CharacterBase)
		{
			Party.Get()->Add(CharacterBase);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("CharacterBase Convert Failure"));
			check(CharacterBase);
		}
	}

	return Party;
}