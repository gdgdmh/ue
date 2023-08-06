// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattleCharacterBase.h"

URpgBattleCharacterBase::URpgBattleCharacterBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BattleCharactaerParameter = NewObject<URpgBattleCharacterParameter>();
}

void URpgBattleCharacterBase::SetParameter(const URpgBattleCharacterParameter& Parameter)
{
	BattleCharactaerParameter.Get()->Copy(Parameter);
}

void URpgBattleCharacterBase::OutputLog()
{
	BattleCharactaerParameter.Get()->OutputLog();
}
