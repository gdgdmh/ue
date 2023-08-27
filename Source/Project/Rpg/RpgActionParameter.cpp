// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgActionParameter.h"

URpgActionParameter::URpgActionParameter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ActionType = ERpgActionType::None;
	AttackParameter = NewObject<URpgAttackParameter>();
	DefenceParameter = NewObject<URpgDefenceParameter>();
}

void URpgActionParameter::SetActionType(ERpgActionType Type)
{
	ActionType = Type;
}

void URpgActionParameter::SetAttackTarget(CPPRpgTargetType TargetType)
{
	check(AttackParameter);
	AttackParameter.Get()->SetTargetType(TargetType);
}

void URpgActionParameter::SetAttackPower(int32 Power)
{
	check(AttackParameter);
	AttackParameter.Get()->SetAttackPower(Power);
}

void URpgActionParameter::SetDefenceTarget(CPPRpgTargetType TargetType)
{
	check(DefenceParameter);
	DefenceParameter.Get()->SetTargetType(TargetType);
}

void URpgActionParameter::SetDefencePower(int32 Power)
{
	check(DefenceParameter);
	DefenceParameter.Get()->SetDefencePower(Power);
}

ERpgActionType URpgActionParameter::GetActionType() const
{
	return ActionType;
}

CPPRpgTargetType URpgActionParameter::GetAttackTarget() const
{
	check(AttackParameter);
	return AttackParameter.Get()->GetTargetType();
}

int32 URpgActionParameter::GetAttackPower() const
{
	check(AttackParameter);
	return AttackParameter.Get()->GetAttackPower();
}

CPPRpgTargetType URpgActionParameter::GetDefenceTarget() const
{
	check(DefenceParameter);
	return DefenceParameter.Get()->GetTargetType();
}

int32 URpgActionParameter::GetDefencePower() const
{
	check(DefenceParameter);
	return DefenceParameter.Get()->GetDefencePower();
}
