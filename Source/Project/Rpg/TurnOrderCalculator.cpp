// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnOrderCalculator.h"

TObjectPtr<UTurnOrderList> UTurnOrderCalculator::Calc(TObjectPtr<URpgBattleParty> EnemyParty)
{
	TObjectPtr<UTurnOrderList> List = NewObject<UTurnOrderList>();
	if (!List)
	{
		return nullptr;
	}

	// 今は愚直に並び順そのまま
	for (TObjectPtr<URpgBattleCharacterBase> CharacterBase : EnemyParty.Get()->GetList())
	{
		List.Get()->Add(CharacterBase);
	}

	// 前はAgilityでのソートをしてたが今は敵の並び順で順番を確定
#if 0
	TArray< TObjectPtr<URpgBattleCharacterBase> > SortTargetAll;

	// ソート対象配列に敵のリストを追加
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
	for (TObjectPtr<URpgBattleCharacterBase> CharacterBase : SortTargetAll)
	{
		List.Get()->Add(CharacterBase);
	}
#endif

	return List;
}