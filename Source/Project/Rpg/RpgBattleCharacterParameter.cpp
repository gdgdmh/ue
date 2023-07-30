﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattleCharacterParameter.h"

URpgBattleCharacterParameter::URpgBattleCharacterParameter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
	, Hp(0)
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

void URpgBattleCharacterParameter::Copy(const URpgBattleCharacterParameter& Parameter)
{
	Hp = Parameter.Hp;
	MaxHp = Parameter.MaxHp;
	Sp = Parameter.Sp;
	MaxSp = Parameter.MaxSp;
	AttackPower = Parameter.AttackPower;
	DefencePower = Parameter.DefencePower;
	Status.Get()->Copy(*Parameter.Status.Get());
}

void URpgBattleCharacterParameter::SetHp(int32 CurrentHp, int32 Max)
{
	this->Hp = CurrentHp;
	this->MaxHp = Max;

	NormalizeHp();
}

void URpgBattleCharacterParameter::SetSp(int32 CurrentSp, int32 Max)
{
	this->Sp = CurrentSp;
	this->MaxSp = Max;

	NormalizeSp();
}

void URpgBattleCharacterParameter::SetAttackPower(int32 Power)
{
	this->AttackPower = Power;
}

void URpgBattleCharacterParameter::SetDefencePower(int32 Power)
{
	this->DefencePower = Power;
}

void URpgBattleCharacterParameter::OutputLog()
{
	UE_LOG(LogTemp, Log, TEXT("Hp:%d MaxHp:%d Sp:%d MaxSp:%d "), Hp, MaxHp, Sp, MaxSp);
	UE_LOG(LogTemp, Log, TEXT("AttackPower:%d DefencePower:%d"), AttackPower, DefencePower);
	Status.Get()->OutputLog();
}