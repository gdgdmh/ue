// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterParameterConverter.h"
#include "RpgBattleCharacter.h"
#include "RpgBattleCharacterEnemy.h"


TWeakObjectPtr<URpgBattleCharacterBase> UCharacterParameterConverter::Convert(const URpgBattleCharacterParameter& Parameter, ESideType SideType)
{
	// 味方の場合はURpgBattleCharacterとして作成
	if (SideType == ESideType::Ally)
	{
		TWeakObjectPtr<URpgBattleCharacter> CharacterBase = NewObject<URpgBattleCharacter>();
		CharacterBase.Get()->SetParameter(Parameter);
		return CharacterBase;
	}
	// 敵の場合はURpgBattleCharacterEnemyとして作成
	else if (SideType == ESideType::Enemy)
	{
		TWeakObjectPtr<URpgBattleCharacterEnemy> CharacterEnemy = NewObject<URpgBattleCharacterEnemy>();
		CharacterEnemy.Get()->SetParameter(Parameter);
		return CharacterEnemy;
	}

	UE_LOG(LogTemp, Log, TEXT("UCharacterParameterConverter::Convert UnknownType"));
	check(false);
	return nullptr;
}