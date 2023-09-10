// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionCardAttackParameter.h"

UActionCardAttackParameter::UActionCardAttackParameter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, AttackPower(0)
{
}

void UActionCardAttackParameter::SetPawer(int32 Power)
{
	AttackPower = Power;
}

int32 UActionCardAttackParameter::GetPower() const
{
	return AttackPower;
}





















