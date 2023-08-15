// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattleManager.h"

URpgBattleManager::URpgBattleManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BattleParty = NewObject<UBattlePartyManager>();
	TurnManager = NewObject<URpgTurnManager>();
}

void URpgBattleManager::SetTurn()
{
	check(TurnManager.IsValid());
	TurnManager.Get()->Set(BattleParty.Get()->Get(ESideType::Ally).Get()->Get(), BattleParty.Get()->Get(ESideType::Enemy).Get()->Get());
}

void URpgBattleManager::OutputTurn() const
{
	check(TurnManager.IsValid());
	TurnManager.Get()->OutputLog();
}

ESideType URpgBattleManager::GetSideType(const TWeakObjectPtr<URpgBattleCharacterBase>& CharacterBase) const
{
	if (!CharacterBase.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::GetSideType CharacterInvalid"));
		check(false);
		return ESideType::Ally;
	}

	for (const auto Character : BattleParty.Get()->Get(ESideType::Ally).Get()->Get()->GetList())
	{
		if (!Character.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::GetSideType Party(Ally) CharacterInvalid"));
			continue;
		}

		if (Character == CharacterBase)
		{
			return ESideType::Ally;
		}
	}

	for (const auto Character : BattleParty.Get()->Get(ESideType::Enemy).Get()->Get()->GetList())
	{
		if (!Character.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::GetSideType Party(Enemy) CharacterInvalid"));
			continue;
		}

		if (Character == CharacterBase)
		{
			return ESideType::Enemy;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::GetSideType Character Not Found"));
	check(false);
	return ESideType::Ally;
}

// 次のステータスに進める
bool URpgBattleManager::NextState()
{
	if (ProcessState == ERpgBattleProcessState::None)
	{
		ProcessState = ERpgBattleProcessState::Initialize;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::Initialize)
	{
		ProcessState = ERpgBattleProcessState::PreStart;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PreStart)
	{
		SetTurn();
		OutputTurn();
		ProcessState = ERpgBattleProcessState::Start;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::Start)
	{
		ProcessState = ERpgBattleProcessState::TurnPreCalc;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::TurnPreCalc)
	{
		ProcessState = ERpgBattleProcessState::TurnCalc;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::TurnCalc)
	{
		ProcessState = ERpgBattleProcessState::TurnCalcFinish;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::TurnCalcFinish)
	{
		ProcessState = ERpgBattleProcessState::TurnPreStart;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::TurnPreStart)
	{
		ProcessState = ERpgBattleProcessState::TurnStart;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::TurnStart)
	{
		ProcessState = ERpgBattleProcessState::ActionSelectWait;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::ActionSelectWait)
	{
		ProcessState = ERpgBattleProcessState::ActionProcess;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::ActionProcess)
	{
		ProcessState = ERpgBattleProcessState::DamageProcess;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::DamageProcess)
	{
		ProcessState = ERpgBattleProcessState::DamageProcessFinish;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::DamageProcessFinish)
	{
		ProcessState = ERpgBattleProcessState::TurnPreFinish;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::TurnPreFinish)
	{
		ProcessState = ERpgBattleProcessState::TurnFinish;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::TurnFinish)
	{
		ProcessState = ERpgBattleProcessState::TurnPreCalc;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PreFinish)
	{
		ProcessState = ERpgBattleProcessState::Finish;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::Finish)
	{
		return true;
	}
	return true;
}


