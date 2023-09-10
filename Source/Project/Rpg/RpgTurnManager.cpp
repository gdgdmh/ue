// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgTurnManager.h"

URpgTurnManager::URpgTurnManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ResetTurnOrderList();
	Calculator = NewObject<UTurnOrderCalculator>();
	TurnCount = DEFAULT_TURN;
}

void URpgTurnManager::ResetTurnOrderList()
{
	List = NewObject<UTurnOrderList>();
}

bool URpgTurnManager::Set(TObjectPtr<URpgBattleParty> EnemyParty)
{
	check(List);
	check(Calculator);
	List = Calculator.Get()->Calc(EnemyParty);
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

void URpgTurnManager::PopFront()
{
	check(List);
	List.Get()->PopFront();
}

void URpgTurnManager::Normalize()
{
	check(List);
	List.Get()->Normalize();
}

TObjectPtr<UTurnOrderList> URpgTurnManager::GetTurnOrderList()
{
	check(List);
	return List;
}

TObjectPtr<UCdCharacterBase> URpgTurnManager::GetCurrentTurnCharacter() const
{
	check(List);
	return List.Get()->GetTopCharacter();
}

bool URpgTurnManager::IsTurnListEmpty() const
{
	check(List);
	if (List.Get()->Size() > 0)
	{
		return false;
	}
	return true;
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
