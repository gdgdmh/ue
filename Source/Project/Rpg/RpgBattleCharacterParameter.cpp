// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattleCharacterParameter.h"

URpgBattleCharacterParameter::URpgBattleCharacterParameter(const FObjectInitializer& ObjectInitializer) :
	Hp(0)
	, MaxHp(0)
	, Sp(0)
	, MaxSp(0)
	, AttackPower(0)
	, DefencePower(0)
{
	Status = NewObject<URpgBattleStatus>();
}

void URpgBattleCharacterParameter::NormalizeHp()
{
	if (MaxHp < Hp)
	{
		Hp = MaxHp;
	}
}

void URpgBattleCharacterParameter::NormalizeSp()
{
	if (MaxSp < Sp)
	{
		Sp = MaxSp;
	}
}