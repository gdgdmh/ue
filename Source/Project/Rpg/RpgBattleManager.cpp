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

bool URpgBattleManager::CheckSideAnnihilation()
{
	check(BattleParty.IsValid());
	TWeakObjectPtr<UBattlePartySide> AllyParty = BattleParty.Get()->Get(ESideType::Ally);
	TWeakObjectPtr<UBattlePartySide> EnemyParty = BattleParty.Get()->Get(ESideType::Enemy);
	check(AllyParty.IsValid());
	check(EnemyParty.IsValid());

	{
		bool bAllDead = true;
		for (const auto Character : AllyParty.Get()->Get()->GetList())
		{
			check(Character.IsValid());
			if (!Character.Get()->GetParameter()->IsDead())
			{
				bAllDead = false;
				break;
			}
		}
		if (bAllDead)
		{
			return true;
		}
	}
	{
		bool bAllDead = true;
		for (const auto Character : EnemyParty.Get()->Get()->GetList())
		{
			check(Character.IsValid());
			if (!Character.Get()->GetParameter()->IsDead())
			{
				bAllDead = false;
				break;
			}
		}
		if (bAllDead)
		{
			return true;
		}
	}
	return false;
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
		// アクション処理
		ActionProc();

		// 全滅していたら終了
		if (CheckSideAnnihilation())
		{
			ProcessState = ERpgBattleProcessState::PreFinish;
			return true;
		}

		ProcessState = ERpgBattleProcessState::ActionProcessFinish;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::ActionProcessFinish)
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
		// 特定の陣営が全滅している
		
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

void URpgBattleManager::ActionProc()
{
	// 攻撃系のアクションか
	if (SelectCommand == ERpgBattleCommandType::Attack)
	{
		
		int32 Damage = 0;
		int32 BeforeHp = 0;
		int32 AfterHp = 0;
		DamageCalc.Get()->Calc(Damage, AttackCharacter, AttackTargetCharacter, SelectCommand);
		BeforeHp = AttackTargetCharacter.Get()->GetParameter().Get()->GetHp();
		AttackTargetCharacter.Get()->Damage(Damage);
		AfterHp = AttackTargetCharacter.Get()->GetParameter().Get()->GetHp();
		UE_LOG(LogTemp, Log, TEXT("%s:%d Damage %d -> %d"),
			*AttackTargetCharacter.Get()->GetParameter().Get()->GetName().ToString(),
			Damage, BeforeHp, AfterHp);
		return;
	}

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

