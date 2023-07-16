// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattleCharacterParameter.h"

URpgBattleCharacterParameter::URpgBattleCharacterParameter() : Hp(0), Sp(0)
{
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