// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattleCharacterBase.h"

URpgBattleCharacterBase::URpgBattleCharacterBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BattleCharactaerParameter = NewObject<URpgBattleCharacterParameter>();
}
