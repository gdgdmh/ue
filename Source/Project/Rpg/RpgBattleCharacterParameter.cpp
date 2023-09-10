// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattleCharacterParameter.h"

URpgBattleCharacterParameter::URpgBattleCharacterParameter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
	, Hp(0)
	, MaxHp(0)
	, Sp(0)
	, MaxSp(0)
	, AttackPower(0)
	, DefencePower(0)
	, Agility(0)
	, EnemyType(ECdEnemyType::None)
{
	Status = NewObject<URpgBattleStatus>();
	Name = FText::FromString("");
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
	Agility = Parameter.Agility;
	Status.Get()->Copy(*Parameter.Status.Get());
	Name = Parameter.Name;
	EnemyType = Parameter.EnemyType;
}

void URpgBattleCharacterParameter::Copy(const FBattlePartyDataTable& PartyDataTable)
{
	Hp = PartyDataTable.Hp;
	MaxHp = PartyDataTable.MaxHp;
	Sp = PartyDataTable.Sp;
	MaxSp = PartyDataTable.MaxSp;
	AttackPower = PartyDataTable.AttackPower;
	DefencePower = PartyDataTable.DefencePower;
	Agility = PartyDataTable.Agility;
	Status.Get()->Copy(*PartyDataTable.Status.Get());
	Name = PartyDataTable.Name;
	EnemyType = ECdEnemyType::None;
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

void URpgBattleCharacterParameter::SetAgility(int32 AgilityValue)
{
	this->Agility = AgilityValue;
}

void URpgBattleCharacterParameter::SetEnemyType(ECdEnemyType Type)
{
	this->EnemyType = Type;
}

void URpgBattleCharacterParameter::Damage(int32 AttackDamage)
{
	check(AttackDamage >= 0); // 回復はここではやらない
	if (IsDead())
	{
		return;
	}

	Hp = Hp - AttackDamage;

	if (IsDead())
	{
		// 攻撃で死亡した
		Status.Get()->AddStatus(ERpgBattleStatusType::Dead);
	}
}

bool URpgBattleCharacterParameter::IsDead() const
{
	// HPが0以下か死亡ステータスなら死亡とみなす
	if (Hp <= 0)
	{
		return true;
	}
	check(Status);
	if (Status.Get()->IsState(ERpgBattleStatusType::Dead))
	{
		return true;
	}
	return false;
}

void URpgBattleCharacterParameter::OutputLog()
{
	UE_LOG(LogTemp, Log, TEXT("Hp:%d MaxHp:%d Sp:%d MaxSp:%d "), Hp, MaxHp, Sp, MaxSp);
	UE_LOG(LogTemp, Log, TEXT("AttackPower:%d DefencePower:%d Agility:%d"), AttackPower, DefencePower, Agility);
	Status.Get()->OutputLog();
	UE_LOG(LogTemp, Log, TEXT("Name:%s EnemyType:%s"), *Name.ToString(), *ToString(EnemyType));
}