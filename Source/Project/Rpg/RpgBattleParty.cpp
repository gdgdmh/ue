// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattleParty.h"

URpgBattleParty::URpgBattleParty()
{
}

URpgBattleParty::URpgBattleParty(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void URpgBattleParty::Add(const TObjectPtr<UCdCharacterBase>& Target)
{
	Characters.Add(Target);
}

void URpgBattleParty::Remove(const TObjectPtr<UCdCharacterBase>& Target)
{
	Characters.Remove(Target);
}

void URpgBattleParty::Clear()
{
	Characters.Empty();
}

void URpgBattleParty::OutputLog()
{
	
	for (int32 i = 0; i < Characters.Num(); ++i)
	{
		UE_LOG(LogTemp, Log, TEXT("--- Character[%d] ---"), i);
		Characters[i].Get()->OutputLog();
	}

}