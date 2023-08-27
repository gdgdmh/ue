// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgBattleManager.h"

URpgBattleManager::URpgBattleManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BattleParty = NewObject<UBattlePartyManager>();
	TurnManager = NewObject<URpgTurnManager>();

	CardList = nullptr;

	SelectCommand = ERpgBattleCommandType::None;
	AttackCharacter = nullptr;
	AttackTargetCharacter = nullptr;

	ActionCardParameter = NewObject<UActionCardParameter>();
}

void URpgBattleManager::SetCardList(TObjectPtr<UActionCardList> List)
{
	CardList = List;
	check(CardList);
}

bool URpgBattleManager::LoadCardParameter()
{
	check(ActionCardParameter);
	FString Path = TEXT("/Game/Project/UI/DataTables/Rpg/Main/DT_CardBaseData.DT_CardBaseData");
	if (!ActionCardParameter.Get()->LoadDataTable(Path))
	{
		UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::LoadCardParameter load failure"));
		return false;
	}

	// テスト
	{
		FActionCardCreateParameter Param;
		Param.SetType(ERpgActionCardType::Attack);
		TObjectPtr<UActionCard> Card = ActionCardParameter.Get()->Create(Param);
		if (Card.Get()->GetActionType() == ERpgActionType::Attack)
		{
			UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::LoadCardParameter create ok"));
		}
	}

	return true;
}

void URpgBattleManager::NormalizeTurnList()
{
	check(TurnManager);
	TurnManager.Get()->Normalize();
}

void URpgBattleManager::SetTurn()
{
	check(TurnManager);
	TurnManager.Get()->Set(BattleParty.Get()->Get(ESideType::Enemy).Get()->Get());
}

void URpgBattleManager::OutputTurnLog() const
{
	check(TurnManager);
	TurnManager.Get()->OutputLog();
}

bool URpgBattleManager::IsTurnListEmpty() const
{
	check(TurnManager);
	return TurnManager.Get()->IsTurnListEmpty();
}

void URpgBattleManager::ChangeTurn()
{
	check(TurnManager);
	if (!TurnManager.Get()->IsTurnListEmpty())
	{
		TurnManager.Get()->PopFront();
	}
}

bool URpgBattleManager::CheckSideAnnihilation()
{
	check(BattleParty);
	TObjectPtr<UBattlePartySide> AllyParty = BattleParty.Get()->Get(ESideType::Ally);
	TObjectPtr<UBattlePartySide> EnemyParty = BattleParty.Get()->Get(ESideType::Enemy);
	check(AllyParty);
	check(EnemyParty);

	{
		bool bAllDead = true;
		for (const auto Character : AllyParty.Get()->Get()->GetList())
		{
			check(Character);
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
			check(Character);
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

ESideType URpgBattleManager::GetSideType(const TObjectPtr<URpgBattleCharacterBase>& CharacterBase) const
{
	if (!CharacterBase)
	{
		UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::GetSideType CharacterInvalid"));
		check(false);
		return ESideType::Ally;
	}

	for (const auto Character : BattleParty.Get()->Get(ESideType::Ally).Get()->Get()->GetList())
	{
		if (!Character)
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
		if (!Character)
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
		ProcessState = ERpgBattleProcessState::PrePlayerTurn;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PrePlayerTurn)
	{
		ProcessState = ERpgBattleProcessState::PlayerSelectAction;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PlayerSelectAction)
	{
		//ProcessState = ERpgBattleProcessState::PlayerAction;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PlayerAction)
	{
		ProcessState = ERpgBattleProcessState::PlayerActionAfter;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PlayerActionAfter)
	{
		ProcessState = ERpgBattleProcessState::PlayerTurnFinish;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PlayerTurnFinish)
	{
		ProcessState = ERpgBattleProcessState::PlayerTurnAfter;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PlayerTurnAfter)
	{
		ProcessState = ERpgBattleProcessState::PlayerTurnAfterFinish;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PlayerTurnAfterFinish)
	{
		ProcessState = ERpgBattleProcessState::PreEnemyTurn;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PreEnemyTurn)
	{
		if (IsTurnListEmpty())
		{
			// ターンリスト初回設定 or 1順した
			// 設定し直し
			SetTurn();
		}
		else
		{
			// 次のメンバーにターンを切り替え
			ChangeTurn();
			if (IsTurnListEmpty())
			{
				SetTurn();
			}
		}
		// 死亡キャラや不正な状態を修正
		NormalizeTurnList();
		OutputTurnLog();

		ProcessState = ERpgBattleProcessState::EnemyAction;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::EnemyAction)
	{
		ProcessState = ERpgBattleProcessState::EnemyActionAfter;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::EnemyActionAfter)
	{
		ProcessState = ERpgBattleProcessState::EnemyActionFinish;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::EnemyActionFinish)
	{
		ProcessState = ERpgBattleProcessState::EnemyTurnAfter;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::EnemyTurnAfter)
	{
		ProcessState = ERpgBattleProcessState::EnemyTurnAfterFinish;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::EnemyTurnAfterFinish)
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
		ProcessState = ERpgBattleProcessState::PreFinish;
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
#if 0
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
		if (IsTurnListEmpty())
		{
			// ターンリスト初回設定 or 1順した
			// 設定し直し
			SetTurn();
		}
		else
		{
			// 次のメンバーにターンを切り替え
			ChangeTurn();
			if (IsTurnListEmpty())
			{
				SetTurn();
			}
		}
		// 死亡キャラや不正な状態を修正
		NormalizeTurnList();
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
#endif
}

// プレイヤーのターンを終了させる
void URpgBattleManager::EndPlayerTurn()
{
	if (ProcessState == ERpgBattleProcessState::PlayerSelectAction)
	{
		ProcessState = ERpgBattleProcessState::PlayerTurnFinish;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Not Player End Turn State"));
	}
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
		FString EnumName = TEXT("/Script/Project.ERpgBattleCommandType");
		UEnum* const Enum = FindObject<UEnum>(nullptr, *EnumName);
		FString CommandEnumName = Enum->GetNameStringByIndex(static_cast<int32>(SelectCommand));
		UE_LOG(LogTemp, Log, TEXT("Command:%s"), *CommandEnumName);
	}
	// 攻撃者
	if (AttackCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("AttackCharacter:%s"), *AttackCharacter.Get()->GetParameter().Get()->GetName().ToString());
	}
	// 攻撃対象者
	if (AttackTargetCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("AttackTargetCharacter:%s"), *AttackTargetCharacter.Get()->GetParameter().Get()->GetName().ToString());
	}
}

