// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionCard.h"

UActionCard::UActionCard(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ActionParameter = NewObject<URpgActionParameter>();
}

void UActionCard::SetActionType(ERpgActionType Type)
{
	check(ActionParameter);
	ActionParameter.Get()->SetActionType(Type);
}

void UActionCard::SetAttackTarget(CPPRpgTargetType TargetType)
{
	check(ActionParameter);
	ActionParameter.Get()->SetAttackTarget(TargetType);
}

void UActionCard::SetAttackPower(int32 Power)
{
	check(ActionParameter);
	ActionParameter.Get()->SetAttackPower(Power);
}

void UActionCard::SetDefenceTarget(CPPRpgTargetType TargetType)
{
	check(ActionParameter);
	ActionParameter.Get()->SetDefenceTarget(TargetType);
}

void UActionCard::SetDefencePower(int32 Power)
{
	check(ActionParameter);
	ActionParameter.Get()->SetDefencePower(Power);
}

ERpgActionType UActionCard::GetActionType() const
{
	check(ActionParameter);
	return ActionParameter.Get()->GetActionType();
}

CPPRpgTargetType UActionCard::GetAttackTarget() const
{
	check(ActionParameter);
	return ActionParameter.Get()->GetAttackTarget();
}

int32 UActionCard::GetAttackPower() const
{
	check(ActionParameter);
	return ActionParameter.Get()->GetAttackPower();
}

CPPRpgTargetType UActionCard::GetDefenceTarget() const
{
	check(ActionParameter);
	return ActionParameter.Get()->GetDefenceTarget();
}

int32 UActionCard::GetDefencePower() const
{
	check(ActionParameter);
	return ActionParameter.Get()->GetDefencePower();
}