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

	CharacterParameter = NewObject<UCdCharacterParameter>();

	ResetSelectCardIndex();
}

void URpgBattleManager::SetCardList(TObjectPtr<UActionCardList> List)
{
	CardList = List;
	check(CardList);
}

bool URpgBattleManager::LoadCardParameter()
{
	// カードパラメーターをデータテーブルから読み込み
	check(ActionCardParameter);
	FString Path = TEXT("/Game/Project/UI/DataTables/Rpg/Main/DT_CardBaseData.DT_CardBaseData");
	if (!ActionCardParameter.Get()->LoadCardDataTable(Path))
	{
		UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::LoadCardParameter load failure"));
		return false;
	}

	// テスト
	{
		FActionCardCreateParameter Param;
		Param.SetCardType(ERpgActionCardType::Attack);
		TObjectPtr<UActionCard> Card = ActionCardParameter.Get()->Create(Param);
		if (Card.Get()->GetActionType() == ERpgActionType::Attack)
		{
			UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::LoadCardParameter create ok"));
		}
	}
	return true;
}

bool URpgBattleManager::LoadDeckParameter()
{
	check(ActionCardParameter);
	FString Path = TEXT("/Game/Project/UI/DataTables/Rpg/Main/DT_DefaultDeckData.DT_DefaultDeckData");
	if (!ActionCardParameter.Get()->LoadDeckDataTable(Path))
	{
		UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::LoadDeckParameter load failure"));
		return false;
	}

	return true;
}

bool URpgBattleManager::LoadCharacterParameter()
{
	check(CharacterParameter);
	{
		FString Path = TEXT("/Game/Project/UI/DataTables/Rpg/Main/DT_PlayerData.DT_PlayerData");
		if (!CharacterParameter.Get()->LoadPlayerDataTable(Path))
		{
			UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::LoadCharacterParameter load failure(player)"));
			return false;
		}
	}
	{
		FString Path = TEXT("/Game/Project/UI/DataTables/Rpg/Main/DT_EnemyData.DT_EnemyData");
		if (!CharacterParameter.Get()->LoadEnemyDataTable(Path))
		{
			UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::LoadCharacterParameter load failure(enemy)"));
			return false;
		}
	}
	return true;
}

void URpgBattleManager::SetPlayer()
{
	TArray<TObjectPtr<UCdCharacterBase> > Players; 
	CharacterParameter.Get()->GetPlayer(Players);

	if (Players.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::SetPlayer failure"));
		check(false);
		return;
	}
	Player = Players[0];
}

void URpgBattleManager::SetEnemies()
{
	TArray<TObjectPtr<UCdCharacterBase> > EnemyData;
	CharacterParameter.Get()->GetEnemy(EnemyData);

	if (EnemyData.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::SetEnemies failure"));
		check(false);
		return;
	}
	Enemies.Empty();
	for (auto Enemy : EnemyData)
	{
		Enemies.Add(Enemy);
	}
}

TArray<TObjectPtr<UCdCharacterBase> > URpgBattleManager::GetEnemy() const
{
	return Enemies;
}

void URpgBattleManager::SetDefaultCardList()
{
	check(ActionCardParameter);
	TObjectPtr<UActionCardList> List = ActionCardParameter.Get()->CreateDefaultDeck();
	if (!List)
	{
		UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::SetDefaultCardList create failure"));
		return;
	}
	CardList.Get()->CopyCard(*List.Get());
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
	TObjectPtr<UBattlePartySide> EnemyParty = BattleParty.Get()->Get(ESideType::Enemy);
	check(EnemyParty);

	// プレイヤーサイドのチェック
	{
		if (Player.Get()->GetParameter()->IsDead())
		{
			return true;
		}
	}
	// 敵サイドのチェック
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
		// 暫定で選択したことにしてしまう
		SelectCardIndex = 0;
		ProcessState = ERpgBattleProcessState::PlayerAction;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PlayerAction)
	{
		if (!ProcessPlayerAction())
		{
			// 何もしなかった
			ProcessState = ERpgBattleProcessState::PlayerActionAfter;
			return true;
		}
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
		// 死亡キャラや不正な状態を修正
		NormalizeTurnList();

		// 全滅していたら終了
		if (CheckSideAnnihilation())
		{
			ProcessState = ERpgBattleProcessState::PreFinish;
			return true;
		}

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
		// ターン設定
		SetTurn();
		// 死亡キャラや不正な状態を修正
		NormalizeTurnList();

		OutputTurnLog();
		ProcessState = ERpgBattleProcessState::EnemyAction;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PreEnemyAction)
	{
		if (IsTurnListEmpty())
		{
			// 敵ターン消化したのでプレイヤーターンへ
			ProcessState = ERpgBattleProcessState::PrePlayerTurn;
			OutputTurnLog();
			return true;
		}
		else
		{
			// 次のメンバーにターンを切り替え
			ChangeTurn();
			if (IsTurnListEmpty())
			{
				// 敵ターン消化したのでプレイヤーターンへ
				ProcessState = ERpgBattleProcessState::PrePlayerTurn;
				return true;
			}
			OutputTurnLog();
		}
		ProcessState = ERpgBattleProcessState::EnemyAction;
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::EnemyAction)
	{
		if (!ProcessEnemyAction())
		{
			// 何もしなかった
			ProcessState = ERpgBattleProcessState::EnemyActionAfter;
			return true;
		}
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
		// 死亡キャラや不正な状態を修正
		NormalizeTurnList();

		// 全滅していたら終了
		if (CheckSideAnnihilation())
		{
			ProcessState = ERpgBattleProcessState::PreFinish;
			return true;
		}

		ProcessState = ERpgBattleProcessState::PreEnemyAction;
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

// 選択カードindexのリセット
void URpgBattleManager::ResetSelectCardIndex()
{
	SelectCardIndex = -1;
}

bool URpgBattleManager::IsSelectCard() const
{
	if (SelectCardIndex == -1)
	{
		// -1は選択してない
		return false;
	}
	return true;
}

// 敵の中で攻撃対象を取得する
TObjectPtr<UCdCharacterBase> URpgBattleManager::GetEnemyAttackTarget()
{
	if (Enemies.IsEmpty())
	{
		return nullptr;
	}

	TObjectPtr<UCdCharacterBase> TargetEnemy = nullptr;
	for (auto Enemy : Enemies)
	{
		if (Enemy.Get()->GetParameter().Get()->IsDead())
		{
			continue;
		}
		return Enemy;
	}
	return nullptr;
}

// プレイヤーのアクション処理
bool URpgBattleManager::ProcessPlayerAction()
{
	const int32 Size = CardList.Get()->GetSize();
	check((0 <= SelectCardIndex) && (SelectCardIndex < Size));

	TObjectPtr<UActionCard> Card = CardList.Get()->GetCard(SelectCardIndex);
	check(Card);
	if (Card.Get()->GetActionType() == ERpgActionType::Attack)
	{
		TObjectPtr<UCdCharacterBase> TargetEnemy = GetEnemyAttackTarget();
		if (TargetEnemy == nullptr)
		{
			// ターゲット取得不可のときは何もしない
			return false;
		}

		int32 Damage = Card.Get()->GetAttackPower();

		int32 BeforeHp = TargetEnemy.Get()->GetParameter().Get()->GetHp();
		TargetEnemy.Get()->Damage(Damage);
		int32 AfterHp = TargetEnemy.Get()->GetParameter().Get()->GetHp();

		UE_LOG(LogTemp, Log, TEXT("%d Damage %d -> %d"),
			Damage, BeforeHp, AfterHp);
	}
	// 死亡キャラや不正な状態を修正
	NormalizeTurnList();

	return true;
}

// 敵のアクション処理
bool URpgBattleManager::ProcessEnemyAction()
{
	TObjectPtr<UCdCharacterBase> TargetCharacter = Player;
	check(TargetCharacter);
	if (TargetCharacter.Get()->GetParameter().Get()->IsDead())
	{
		return false;
	}

	TObjectPtr<UCdCharacterBase> TurnCharacter = TurnManager.Get()->GetCurrentTurnCharacter();
	check(TurnCharacter);

	int32 Damage = TurnCharacter.Get()->GetParameter().Get()->GetAttackPower();

	int32 BeforeHp = TargetCharacter.Get()->GetParameter().Get()->GetHp();
	TargetCharacter.Get()->Damage(Damage);
	int32 AfterHp = TargetCharacter.Get()->GetParameter().Get()->GetHp();
	UE_LOG(LogTemp, Log, TEXT("%d Player Damage %d -> %d"),
		Damage, BeforeHp, AfterHp);

	return true;
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

