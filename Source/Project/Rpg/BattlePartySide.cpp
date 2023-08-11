// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePartySide.h"

UBattlePartySide::UBattlePartySide(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Party = NewObject<URpgBattleParty>();
	Type = ESideType::Ally;
}