﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattleCharacterBase.h"

URpgBattleCharacterBase::URpgBattleCharacterBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BattleCharactaerParameter = NewObject<URpgBattleCharacterParameter>();
}

void URpgBattleCharacterBase::SetParameter(const URpgBattleCharacterParameter& Parameter)
{
	check(BattleCharactaerParameter);
	BattleCharactaerParameter.Get()->Copy(Parameter);
}

void URpgBattleCharacterBase::Damage(int32 AttackDamage)
{
	check(BattleCharactaerParameter);
	BattleCharactaerParameter.Get()->Damage(AttackDamage);
}

void URpgBattleCharacterBase::OutputLog()
{
	check(BattleCharactaerParameter);
	BattleCharactaerParameter.Get()->OutputLog();
}
