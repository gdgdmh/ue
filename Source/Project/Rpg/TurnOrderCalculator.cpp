// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnOrderCalculator.h"

TObjectPtr<UTurnOrderList> UTurnOrderCalculator::Calc(TObjectPtr<URpgBattleParty> AllyParty, TObjectPtr<URpgBattleParty> EnemyParty)
{
	TObjectPtr<UTurnOrderList> List = NewObject<UTurnOrderList>();
	if (!List)
	{
		return nullptr;
	}

	TArray< TObjectPtr<URpgBattleCharacterBase> > SortTargetAll;

	// ソート対象配列に味方と敵のリストを追加
	{
		const TArray<TObjectPtr<URpgBattleCharacterBase> > TargetList = AllyParty.Get()->GetList();
		for (const TObjectPtr<URpgBattleCharacterBase> CharacterBase : TargetList)
		{
			SortTargetAll.Add(CharacterBase);
		}
	}
	{
		const TArray<TObjectPtr<URpgBattleCharacterBase> > TargetList = EnemyParty.Get()->GetList();
		for (const TObjectPtr<URpgBattleCharacterBase> CharacterBase : TargetList)
		{
			SortTargetAll.Add(CharacterBase);
		}
	}

	// Agilityの大きさでソート
	SortTargetAll.Sort([](const URpgBattleCharacterBase& A, const URpgBattleCharacterBase& B) {
		return A.GetParameter().Get()->GetAgility() > B.GetParameter().Get()->GetAgility();
	});
	/*
	SortTargetAll.Sort([](const TObjectPtr<URpgBattleCharacterBase>& A, const TObjectPtr<URpgBattleCharacterBase>& B) {
		return A.Get()->GetParameter().Get()->GetAgility() > B.Get()->GetParameter().Get()->GetAgility();
	});
	*/

	for (TObjectPtr<URpgBattleCharacterBase> CharacterBase : SortTargetAll)
	{
		List.Get()->Add(CharacterBase);
	}

	return List;
}