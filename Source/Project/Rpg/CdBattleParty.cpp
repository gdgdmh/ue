// Fill out your copyright notice in the Description page of Project Settings.


#include "CdBattleParty.h"


UCdBattleParty::UCdBattleParty(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCdBattleParty::Add(const TObjectPtr<UCdCharacterBase>& Target)
{
	Characters.Add(Target);
}

void UCdBattleParty::Remove(const TObjectPtr<UCdCharacterBase>& Target)
{
	Characters.Remove(Target);
}

void UCdBattleParty::Clear()
{
	Characters.Empty();
}

void UCdBattleParty::OutputLog()
{
	for (int32 i = 0; i < Characters.Num(); ++i)
	{
		UE_LOG(LogTemp, Log, TEXT("--- Character[%d] ---"), i);
		Characters[i].Get()->OutputLog();
	}
}
