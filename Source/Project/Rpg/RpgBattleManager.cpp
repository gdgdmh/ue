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
	AttackTargetEnemy = nullptr;

	ActionCardParameter = NewObject<UActionCardParameter>();

	CharacterParameter = NewObject<UCdCharacterParameter>();

	// 敵行動パラメーター
	EnemyActionParameter = NewObject<UEnemyActionParameter>();
	EnemyActionParameter->Test();
	// 敵行動パラメーター(集合体)
	EnemyAndEnemyActionParameter = NewObject<UEnemyAndEnemyActionDataParameter>();

	ResetSelectCardIndex();

	bSelectTarget = false;

	SelectableEnemyNum = 0;
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

bool URpgBattleManager::LoadEnemyActionParameter()
{
	check(EnemyActionParameter);

	FString Path = TEXT("/Game/Project/Enemy/Cd/DataTables/DT_EnemyActionData.DT_EnemyActionData");
	if (!EnemyActionParameter.Get()->LoadDataTable(Path))
	{
		UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::LoadEnemyActionParameter load failure(enemy action)"));
		return false;
	}

	EnemyActionParameter.Get()->Test();
	return true;
}

bool URpgBattleManager::LoadEnemyAndEnemyActionParameter()
{
	check(EnemyAndEnemyActionParameter);
	FString Path = TEXT("/Game/Project/UI/DataTables/Rpg/Main/Enemy/DT_EnemyActionDatas.DT_EnemyActionDatas");
	if (!EnemyAndEnemyActionParameter.Get()->LoadDataTable(Path))
	{
		UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::LoadEnemyActionParameter load failure(enemy action)"));
		return false;
	}
	EnemyAndEnemyActionParameter.Get()->Test();
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

int32 URpgBattleManager::GetPlayerHp() const
{
	check(Player);
	return Player.Get()->GetParameter().Get()->GetHp();
}

int32 URpgBattleManager::GetPlayerMaxHp() const
{
	check(Player);
	return Player.Get()->GetParameter().Get()->GetMaxHp();
}

// 次のステータスに進める
bool URpgBattleManager::NextState()
{
	if (ProcessState == ERpgBattleProcessState::None)
	{
		SetProcessState(ERpgBattleProcessState::Initialize);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::Initialize)
	{
		SetProcessState(ERpgBattleProcessState::PreStart);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PreStart)
	{
		SetProcessState(ERpgBattleProcessState::Start);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::Start)
	{
		SetProcessState(ERpgBattleProcessState::PrePlayerTurn);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PrePlayerTurn)
	{
		// 暫定で対象を1つ選択できることにしてしまう
		//SelectableEnemyNum = 1;

		SetProcessState(ERpgBattleProcessState::PlayerSelectAction);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PlayerSelectAction)
	{
		// 暫定で選択したことにしてしまう
		SelectCardIndex = 0;


		TObjectPtr<UActionCard> Card = CardList.Get()->GetCard(SelectCardIndex);
		check(Card);
		if (Card.Get()->GetActionType() == ERpgActionType::Attack)
		{
			if (Card.Get()->GetAttackTarget() == ERpgTargetType::Single)
			{
				SelectableEnemyNum = 1;
			}
		}

		// クリア
		AttackTargetEnemy = nullptr;

		SetProcessState(ERpgBattleProcessState::PlayerSelectTarget);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PlayerSelectTarget)
	{
		SetProcessState(ERpgBattleProcessState::PlayerAction);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PlayerAction)
	{

		// リセット
		SelectableEnemyNum = 0;

		if (!ProcessPlayerAction())
		{
			// 何もしなかった
			SetProcessState(ERpgBattleProcessState::PlayerActionAfter);
			return true;
		}
		ChangeEnemyInfoDelegate.ExecuteIfBound();
		SetProcessState(ERpgBattleProcessState::PlayerActionAfter);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PlayerActionAfter)
	{
		AttackTargetEnemy = nullptr;

		SetProcessState(ERpgBattleProcessState::PlayerTurnFinish);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PlayerTurnFinish)
	{
		// 死亡キャラや不正な状態を修正
		NormalizeTurnList();

		// 全滅していたら終了
		if (CheckSideAnnihilation())
		{
			SetProcessState(ERpgBattleProcessState::PreFinish);
			return true;
		}

		SetProcessState(ERpgBattleProcessState::PlayerTurnAfter);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PlayerTurnAfter)
	{
		SetProcessState(ERpgBattleProcessState::PlayerTurnAfterFinish);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PlayerTurnAfterFinish)
	{
		SetProcessState(ERpgBattleProcessState::PreEnemyTurn);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PreEnemyTurn)
	{
		// ターン設定
		SetTurn();
		// 死亡キャラや不正な状態を修正
		NormalizeTurnList();

		OutputTurnLog();
		SetProcessState(ERpgBattleProcessState::EnemyAction);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PreEnemyAction)
	{
		if (IsTurnListEmpty())
		{
			// 敵ターン消化したのでプレイヤーターンへ
			SetProcessState(ERpgBattleProcessState::PrePlayerTurn);
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
				SetProcessState(ERpgBattleProcessState::PrePlayerTurn);
				return true;
			}
			OutputTurnLog();
		}
		SetProcessState(ERpgBattleProcessState::EnemyAction);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::EnemyAction)
	{
		if (!ProcessEnemyAction())
		{
			// 何もしなかった
			SetProcessState(ERpgBattleProcessState::EnemyActionAfter);
			return true;
		}
		ChangePlayerInfoDelegate.ExecuteIfBound(); // プレイヤー情報更新Delegate
		SetProcessState(ERpgBattleProcessState::EnemyActionAfter);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::EnemyActionAfter)
	{
		SetProcessState(ERpgBattleProcessState::EnemyActionFinish);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::EnemyActionFinish)
	{

		SetProcessState(ERpgBattleProcessState::EnemyTurnAfter);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::EnemyTurnAfter)
	{
		SetProcessState(ERpgBattleProcessState::EnemyTurnAfterFinish);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::EnemyTurnAfterFinish)
	{
		SetProcessState(ERpgBattleProcessState::TurnPreFinish);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::TurnPreFinish)
	{
		SetProcessState(ERpgBattleProcessState::TurnFinish);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::TurnFinish)
	{
		// 死亡キャラや不正な状態を修正
		NormalizeTurnList();

		// 全滅していたら終了
		if (CheckSideAnnihilation())
		{
			SetProcessState(ERpgBattleProcessState::PreFinish);
			return true;
		}

		SetProcessState(ERpgBattleProcessState::PreEnemyAction);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::PreFinish)
	{
		SetProcessState(ERpgBattleProcessState::Finish);
		return true;
	}
	if (ProcessState == ERpgBattleProcessState::Finish)
	{
		return true;
	}
	return true;
}

void URpgBattleManager::SetProcessState(ERpgBattleProcessState State)
{
	ProcessState = State;
	ChangeProcessStateDelegate.ExecuteIfBound(ProcessState);
}

// プレイヤーのターンを終了させる
void URpgBattleManager::EndPlayerTurn()
{
	if (ProcessState == ERpgBattleProcessState::PlayerSelectAction)
	{
		
		SetProcessState(ERpgBattleProcessState::PlayerTurnFinish);
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
		TObjectPtr<UCdCharacterBase> TargetEnemy = nullptr;
		if (AttackTargetEnemy != nullptr)
		{
			// 手動選択
			TargetEnemy = AttackTargetEnemy;
		}
		else
		{
			TargetEnemy = GetEnemyAttackTarget();
		}

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

	check(EnemyActionParameter);
	int32 Damage = TurnCharacter.Get()->GetParameter().Get()->GetAttackPower() + EnemyActionParameter.Get()->GetSimpleAttack().GetAttackPower();

	int32 BeforeHp = TargetCharacter.Get()->GetParameter().Get()->GetHp();
	TargetCharacter.Get()->Damage(Damage);
	int32 AfterHp = TargetCharacter.Get()->GetParameter().Get()->GetHp();
	UE_LOG(LogTemp, Log, TEXT("%d Player Damage %d -> %d"),
		Damage, BeforeHp, AfterHp);

	return true;
}

// 敵ウィジェットが選択されたとき
void URpgBattleManager::OnClickEnemyInfo(TObjectPtr<UCdCharacterBase> Enemy, bool isSelect)
{
	if (!IsEnableSelectEnemy())
	{
		UE_LOG(LogTemp, Log, TEXT("URpgBattleManager::OnClickEnemyInfo Not Select Timing"));
		return;
	}

	if (!isSelect)
	{
		// 非選択状態
		AttackTargetEnemy = nullptr;
		bSelectTarget = false;
	}
	else
	{
		// 選択状態
		AttackTargetEnemy = Enemy;
		bSelectTarget = true;
	}
}

// 敵の選択が可能なタイミングか
bool URpgBattleManager::IsEnableSelectEnemy() const
{
	// 今はStateで判断する
	// 細かい判定が必要になった場合はフラグなどで判定すること
	if (ProcessState == ERpgBattleProcessState::PlayerSelectTarget)
	{
		return true;
	}
	return false;
}

// 選択可能な敵の数を取得
int32 URpgBattleManager::GetSelectableEnemyNum() const
{
	return SelectableEnemyNum;
}

FRpgBattleManagerChangePlayerInfoDelegate& URpgBattleManager::GetChangePlayerInfoDelegate()
{
	return ChangePlayerInfoDelegate;
}

FRpgBattleManagerChangeEnemyInfoDelegate& URpgBattleManager::GetChangeEnemyInfoDelegate()
{
	return ChangeEnemyInfoDelegate;
}

FRpgBattleMangerChangeProcessStateDelegate& URpgBattleManager::GetChangeProcessStateDelegate()
{
	return ChangeProcessStateDelegate;
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

