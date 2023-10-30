// Fill out your copyright notice in the Description page of Project Settings.


#include "CdCharacterParameter.h"

#include "../Common/DataTableUtility.h"


UCdCharacterParameter::UCdCharacterParameter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCdCharacterParameter::LoadPlayerDataTable(const FString& DataTableReferencePath)
{
#if 1
	TObjectPtr<UDataTableUtility> util = NewObject<UDataTableUtility>();

	UDataTableUtility::LoadStatus Status = util->LoadDataTable<FCdCharacterDataTable>(PlayerData, DataTableReferencePath);
	if ((Status == UDataTableUtility::LoadStatus::Success) || (Status == UDataTableUtility::LoadStatus::FailureEmptyData))
	{
		return true;
	}
	return false;
#endif

}

bool UCdCharacterParameter::LoadEnemyDataTable(const FString& DataTableReferencePath)
{
#if 1
	TObjectPtr<UDataTableUtility> util = NewObject<UDataTableUtility>();

	UDataTableUtility::LoadStatus Status = util->LoadDataTable<FCdCharacterDataTable>(EnemyData, DataTableReferencePath);
	if ((Status == UDataTableUtility::LoadStatus::Success) || (Status == UDataTableUtility::LoadStatus::FailureEmptyData))
	{
		return true;
	}
	return false;
#endif
}

void UCdCharacterParameter::GetPlayer(TArray<TObjectPtr<UCdCharacterBase> >& Player) const
{
	check(!PlayerData.IsEmpty());

	Player.Empty();
	for (auto Character : PlayerData)
	{
		TObjectPtr<UCdCharacterBase> CharacterBase = NewObject<UCdCharacterBase>();
		CharacterBase.Get()->GetParameter().Get()->SetHp(Character.GetHp(), Character.GetMaxHp());
		CharacterBase.Get()->GetParameter().Get()->SetAttackPower(Character.GetAttackPower());
		CharacterBase.Get()->GetParameter().Get()->SetDefencePower(Character.GetDefencePower());
		CharacterBase.Get()->GetParameter().Get()->SetEnemyType(ECdEnemyType::None);
		Player.Add(CharacterBase);
	}
}

void UCdCharacterParameter::GetEnemy(TArray<TObjectPtr<UCdCharacterBase> >& Enemies) const
{
	check(!EnemyData.IsEmpty());

	Enemies.Empty();
	for (auto Character : EnemyData)
	{
		TObjectPtr<UCdCharacterBase> CharacterBase = NewObject<UCdCharacterBase>();
		CharacterBase.Get()->GetParameter().Get()->SetHp(Character.GetHp(), Character.GetMaxHp());
		CharacterBase.Get()->GetParameter().Get()->SetAttackPower(Character.GetAttackPower());
		CharacterBase.Get()->GetParameter().Get()->SetDefencePower(Character.GetDefencePower());
		CharacterBase.Get()->GetParameter().Get()->SetEnemyType(Character.GetEnemyType());
		Enemies.Add(CharacterBase);
	}
}
