// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionCardDefenceParameter.h"

UActionCardDefenceParameter::UActionCardDefenceParameter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, DefencePower(0)
{
}

void UActionCardDefenceParameter::SetPawer(int32 Power)
{
	DefencePower = Power;
}

int32 UActionCardDefenceParameter::GetPower() const
{
	return DefencePower;
}
