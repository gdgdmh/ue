// Fill out your copyright notice in the Description page of Project Settings.


#include "CdCharacterBase.h"


UCdCharacterBase::UCdCharacterBase(const FObjectInitializer& ObjectInitializer)
{
	BattleCharactaerParameter = NewObject<URpgBattleCharacterParameter>();
}

void UCdCharacterBase::SetParameter(const URpgBattleCharacterParameter& Parameter)
{
	check(BattleCharactaerParameter);
	BattleCharactaerParameter.Get()->Copy(Parameter);
}

void UCdCharacterBase::Damage(int32 AttackDamage)
{
	check(BattleCharactaerParameter);
	BattleCharactaerParameter.Get()->Damage(AttackDamage);
}

void UCdCharacterBase::OutputLog()
{
	check(BattleCharactaerParameter);
	BattleCharactaerParameter.Get()->OutputLog();
}