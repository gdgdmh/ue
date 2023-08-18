// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgTurnManager.h"

URpgTurnManager::URpgTurnManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ResetTurnOrderList();
	Calculator = NewObject<UTurnOrderCalculator>();
}

void URpgTurnManager::ResetTurnOrderList()
{
	List = NewObject<UTurnOrderList>();
}

bool URpgTurnManager::Set(TObjectPtr<URpgBattleParty> AllyParty, TObjectPtr<URpgBattleParty> EnemyParty)
{
	check(Calculator);
	List = Calculator.Get()->Calc(AllyParty, EnemyParty);
	if (!List)
	{
		UE_LOG(LogTemp, Log, TEXT("URpgTurnManager::Set Failure"));
		// 何かしらのエラーが出てしまった
		// 最低限参照はできるようにリセット
		ResetTurnOrderList();
		return false;
	}
	return true;
}

TObjectPtr<UTurnOrderList> URpgTurnManager::GetTurnOrderList()
{
	check(List);
	return List;
}

TObjectPtr<URpgBattleCharacterBase> URpgTurnManager::GetCurrentTurnCharacter() const
{
	check(List);
	return List.Get()->GetTopCharacter();
}

void URpgTurnManager::OutputLog() const
{
	if (!List)
	{
		UE_LOG(LogTemp, Log, TEXT("URpgTurnManager::OutputLog List Invalid"));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("--- TurnList start ---"));
	List.Get()->OutputLog();
	UE_LOG(LogTemp, Log, TEXT("--- TurnList end ---"));
}
