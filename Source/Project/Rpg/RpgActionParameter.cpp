// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgActionParameter.h"

URpgActionParameter::URpgActionParameter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AttackParameter = NewObject<URpgAttackParameter>();
	DefenceParameter = NewObject<URpgDefenceParameter>();
}

