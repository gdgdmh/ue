// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnOrderCalculator.h"

TWeakObjectPtr<UTurnOrderList> UTurnOrderCalculator::Calc(TWeakObjectPtr<URpgBattleParty> AllyParty, TWeakObjectPtr<URpgBattleParty> EnemyParty)
{
	TWeakObjectPtr<UTurnOrderList> List = NewObject<UTurnOrderList>();
	if (!List.IsValid())
	{
		return nullptr;
	}

	TArray< TWeakObjectPtr<URpgBattleCharacterBase> > SortTargetAll;

	// �\�[�g�Ώ۔z��ɖ����ƓG�̃��X�g��ǉ�
	{
		const TArray<TWeakObjectPtr<URpgBattleCharacterBase> > TargetList = AllyParty.Get()->GetList();
		for (const TWeakObjectPtr<URpgBattleCharacterBase> CharacterBase : TargetList)
		{
			SortTargetAll.Add(CharacterBase);
		}
	}
	{
		const TArray<TWeakObjectPtr<URpgBattleCharacterBase> > TargetList = EnemyParty.Get()->GetList();
		for (const TWeakObjectPtr<URpgBattleCharacterBase> CharacterBase : TargetList)
		{
			SortTargetAll.Add(CharacterBase);
		}
	}

	// Agility�̑傫���Ń\�[�g
	SortTargetAll.Sort([](const TWeakObjectPtr<URpgBattleCharacterBase>& A, const TWeakObjectPtr<URpgBattleCharacterBase>& B) {
		return A.Get()->GetParameter().Get()->GetAgility() > B.Get()->GetParameter().Get()->GetAgility();
	});

	for (TWeakObjectPtr<URpgBattleCharacterBase> CharacterBase : SortTargetAll)
	{
		List.Get()->Add(CharacterBase);
	}

	return List;
}