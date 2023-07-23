// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattleParty.h"

URpgBattleParty::URpgBattleParty(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void URpgBattleParty::Add(const TWeakObjectPtr<URpgBattleCharacter>& Target)
{
	Characters.Add(Target);
}

void URpgBattleParty::Remove(const TWeakObjectPtr<URpgBattleCharacter>& Target)
{
	Characters.Remove(Target);
}

void URpgBattleParty::Clear()
{
	Characters.Empty();
}