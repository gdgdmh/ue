// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattleManager.h"

URpgBattleManager::URpgBattleManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BattleParty = NewObject<UBattlePartyManager>();
	TurnManager = NewObject<URpgTurnManager>();

	SelectCommand = ERpgBattleCommandType::None;
	AttackCharacter = nullptr;
	AttackTargetCharacter = nullptr;
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
		SetTurn();
		OutputTurn();
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
		// ターン開始時の処理

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
		// 本当は自分で選ばせる
		// 今は固定
		SelectCommand = ERpgBattleCommandType::Attack;
		AttackCharacter = TurnManager.Get()->GetCurrentTurnCharacter();
		{
			ESideType Type = GetSideType(AttackCharacter);
			ESideType EnemyType = GetEnemySide(Type);
			AttackTargetCharacter = BattleParty.Get()->GetAttackTarget(EnemyType);
		}

		UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::NextState ActionProcess"));
		OutputSelectCommandLog();

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

// 行動選択のログ出力
void URpgBattleManager::OutputSelectCommandLog()
{
	// コマンドの出力(EnumからFStringに変換)
	{
		FString EnumName = TEXT("ERpgBattleCommandType");
		UEnum* const Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName);
		FString CommandEnumName = Enum->GetNameStringByIndex(static_cast<int32>(SelectCommand));
		UE_LOG(LogTemp, Log, TEXT("Command:%s"), *CommandEnumName);
	}
	// 攻撃者
	if (AttackCharacter.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("AttackCharacter:%s"), *AttackCharacter.Get()->GetParameter().Get()->GetName().ToString());
	}
	// 攻撃対象者
	if (AttackTargetCharacter.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("AttackTargetCharacter:%s"), *AttackTargetCharacter.Get()->GetParameter().Get()->GetName().ToString());
	}
}

