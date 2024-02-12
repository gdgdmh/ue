﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectRpgGameMode.h"
#include "RpgCharaInfo.h"
#include "RpgTitleUserWidget.h"
#include "RpgMainUserWidget.h"

#include "BattlePartyDataTableLoader.h"
#include "BattlePartyDataTableConverter.h"

// --- test ---
#include "TurnOrderList.h"
#include "TurnOrderCalculator.h"
// ---


AProjectRpgGameMode::AProjectRpgGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = APawn::StaticClass();
	//PlayerControllerClass = AMatch3PlayerController::StaticClass();
	//bTasking = false;
}

void AProjectRpgGameMode::BeginPlay()
{
	UE_LOG(LogTemp, Log, TEXT("AProjectRpgGameMode::BeginPlay"));
	Super::BeginPlay();
	// タイトルUIをセット
	SetTitleUI();
}

void AProjectRpgGameMode::OnDelegateRpgTitleUserWidgetSelect(ERpgTitleUserWidgetSelectType Type)
{
	// タイトルのDelegate(選択結果)
	if (Type == ERpgTitleUserWidgetSelectType::Start)
	{
		UE_LOG(LogTemp, Log, TEXT("AProjectRpgGameMode::OnDelegateRpgTitleUserWidgetSelect Start"));
		// タイトルUIの削除
		CleanupTitleUI();

		// 戦闘システム初期化
		InitializeBattleManager();

		// メインUIのセット
		SetMainUI();
	}
	else if (Type == ERpgTitleUserWidgetSelectType::Test)
	{
		UE_LOG(LogTemp, Log, TEXT("AProjectRpgGameMode::OnDelegateRpgTitleUserWidgetSelect Test"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AProjectRpgGameMode::OnDelegateRpgTitleUserWidgetSelect Unknown"));
	}
}

void AProjectRpgGameMode::SetTitleUI()
{
	if (TitleProjectUserWidgets.Num() != 0)
	{
		// 初期化前に0以外なのはおかしい
		UE_LOG(LogTemp, Log, TEXT("AProjectRpgGameMode::BeginPlay TitleProjectUserWidgets != 0"));
	}

	// RootのWBP
	{
		FString AssetPath = TEXT("/Game/Project/UI/Blueprints/Rpg/Title/WBP_RpgTitleRoot.WBP_RpgTitleRoot_C");
		TSubclassOf<class UUserWidget> WidgetClass;
		WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
		if (!WidgetClass)
		{
			UE_LOG(LogTemp, Log, TEXT("widget load failure"));
			return;
		}

		TObjectPtr<UProjectUserWidget> RootWidget = CreateWidget<UProjectUserWidget>(GetWorld(), WidgetClass);
		if (RootWidget)
		{
			RootWidget->AddToViewport(20);
			RootWidget->AddUserWidgetSubsytem();
			TitleProjectUserWidgets.Add(RootWidget);
		}
	}

	// タイトルメインWBP
	{
		FString AssetPath = TEXT("/Game/Project/UI/Blueprints/Rpg/Title/WBP_RpgTitle.WBP_RpgTitle_C");
		TSubclassOf<class UUserWidget> WidgetClass;
		WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
		if (!WidgetClass)
		{
			UE_LOG(LogTemp, Log, TEXT("widget load failure"));
			return;
		}

		TObjectPtr<URpgTitleUserWidget> TitleWidget = CreateWidget<URpgTitleUserWidget>(GetWorld(), WidgetClass);
		if (TitleWidget)
		{
			TitleWidget->AddToViewport(20);
			TitleWidget->AddUserWidgetSubsytem();
			TitleProjectUserWidgets.Add(TitleWidget);

			TitleWidget->RpgTitleDelegate.BindLambda([this](ERpgTitleUserWidgetSelectType Type)
				{
					OnDelegateRpgTitleUserWidgetSelect(Type);
				});
		}
	}
}

void AProjectRpgGameMode::CleanupTitleUI()
{
	// 登録とは逆順にViewportから開放&サブシステムから削除
	for (int32 i = TitleProjectUserWidgets.Num() - 1; i >= 0; --i)
	{
		if ((i < 0) || (i >= TitleProjectUserWidgets.Num()))
		{
			UE_LOG(LogTemp, Warning, TEXT("AProjectRpgGameMode::CleanupTitleUI index error"));
			continue;
		}
		TitleProjectUserWidgets[i]->RemoveFromParent();
		TitleProjectUserWidgets[i]->RemoveUserWidgetSubsystem();
	}
	TitleProjectUserWidgets.Empty();
}

void AProjectRpgGameMode::SetMainUI()
{
	/*
	// パーティ作成のテスト
	{
		UE_LOG(LogTemp, Log, TEXT("--- Party Factory Test Begin ---"));
		TObjectPtr<URpgBattlePartyFactory> Factory = NewObject<URpgBattlePartyFactory>();
		AllyParty = Factory->Create(ERpgBattlePartyFactoryType::Test);
		EnemyParty = Factory->Create(ERpgBattlePartyFactoryType::TestEnemy);
		UE_LOG(LogTemp, Log, TEXT("--- Party Factory Test End ---"));
	}

	// 味方パーティをデータテーブルから読み込み
	UE_LOG(LogTemp, Log, TEXT("--- DataTable Load Ally Party ---"));
	{
		TObjectPtr<UBattlePartyDataTableLoader> Loader = NewObject<UBattlePartyDataTableLoader>();
		FString DataTablePath = "/Script/Engine.DataTable'/Game/Project/UI/DataTables/Rpg/DT_BattlePartyAlly.DT_BattlePartyAlly'";
		TArray<FBattlePartyDataTable> PartyDataTable;
		if (Loader.Get()->Load(DataTablePath, PartyDataTable))
		{
			// 読み込んだテーブルからパーティを作成
			TObjectPtr<UBattlePartyDataTableConverter> Converter = NewObject<UBattlePartyDataTableConverter>();
			AllyParty = Converter.Get()->Convert(PartyDataTable, ESideType::Ally);
			AllyParty->OutputLog();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("BattlePartyDataTable Load Failure"));
		}
	}

	// 敵パーティをデータテーブルから読み込み
	UE_LOG(LogTemp, Log, TEXT("--- DataTable Load Enemy Party ---"));
	{
		TObjectPtr<UBattlePartyDataTableLoader> Loader = NewObject<UBattlePartyDataTableLoader>();
		FString DataTablePath = "/Script/Engine.DataTable'/Game/Project/UI/DataTables/Rpg/DT_BattlePartyEnemy.DT_BattlePartyEnemy'";
		TArray<FBattlePartyDataTable> PartyDataTable;
		if (Loader.Get()->Load(DataTablePath, PartyDataTable))
		{
			// 読み込んだテーブルからパーティを作成
			TObjectPtr<UBattlePartyDataTableConverter> Converter = NewObject<UBattlePartyDataTableConverter>();
			EnemyParty = Converter.Get()->Convert(PartyDataTable, ESideType::Enemy);
			EnemyParty->OutputLog();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("BattlePartyDataTable Load Failure"));
		}
	}
	*/

	// ターンソートのテスト
	/*
	{
		TObjectPtr<UTurnOrderCalculator> Calc = NewObject<UTurnOrderCalculator>();
		TObjectPtr<UTurnOrderList> List = Calc.Get()->Calc(AllyParty, EnemyParty);

		UE_LOG(LogTemp, Log, TEXT("--- SortTest Begin ---"));
		{
			const int32 Num = List.Get()->Size();
			for (int32 i = 0; i < Num; ++i)
			{
				List.Get()->Get(i).Get()->OutputLog();
			}
		}
		UE_LOG(LogTemp, Log, TEXT("--- SortTest End ---"));
		List.Get()->PopFront();
		{
			const int32 Num = List.Get()->Size();
			for (int32 i = 0; i < Num; ++i)
			{
				List.Get()->Get(i).Get()->OutputLog();
			}
		}
		UE_LOG(LogTemp, Log, TEXT("--- SortTest End ---"));
	}
	*/

	// BattleManager
	{
		//BattleManager = NewObject<URpgBattleManager>();
		check(BattleManager);
		//check(AllyParty);
		//check(EnemyParty);


		TObjectPtr<UBattlePartyManager> BattleParty = NewObject<UBattlePartyManager>();
		BattleParty->Initialize();
		/*
		{
			TObjectPtr<UBattlePartySide> AllyPartySide = NewObject<UBattlePartySide>();
			AllyPartySide.Get()->SetParty(AllyParty);
			AllyPartySide.Get()->SetType(ESideType::Ally);
			BattleParty->SetParty(AllyPartySide);
		}
		{
			TObjectPtr<UBattlePartySide> EnemyPartySide = NewObject<UBattlePartySide>();
			EnemyPartySide.Get()->SetParty(EnemyParty);
			EnemyPartySide.Get()->SetType(ESideType::Enemy);
			BattleParty->SetParty(EnemyPartySide);
		}
		*/

		check(CardList);
		BattleManager.Get()->SetCardList(CardList);

		BattleManager.Get()->LoadCardParameter();
		BattleManager.Get()->LoadDeckParameter();
		BattleManager.Get()->SetDefaultCardList();

		BattleManager.Get()->LoadCharacterParameter();
		BattleManager.Get()->LoadEnemyActionParameter();
		BattleManager.Get()->LoadEnemyAndEnemyActionParameter();

		BattleManager.Get()->SetPlayer();
		BattleManager.Get()->SetEnemies();

		BattleManager.Get()->SetupEnemyAndEnemyActionAssociator();


		AllyParty = NewObject<URpgBattleParty>();
		EnemyParty = NewObject<URpgBattleParty>();
		{
			TObjectPtr<UBattlePartySide> EnemyPartySide = NewObject<UBattlePartySide>();
			TArray<TObjectPtr<UCdCharacterBase> > Enemies = BattleManager.Get()->GetEnemy();
			for (TObjectPtr<UCdCharacterBase> Enemy : Enemies)
			{
				EnemyParty->Add(Enemy);
			}
			EnemyPartySide.Get()->SetParty(EnemyParty);
			EnemyPartySide.Get()->SetType(ESideType::Enemy);
			BattleParty->SetParty(EnemyPartySide);
		}


		BattleManager.Get()->SetBattleParty(BattleParty);

	}

	if (MainProjectUserWidgets.Num() != 0)
	{
		// 初期化前に0以外なのはおかしい
		UE_LOG(LogTemp, Log, TEXT("AProjectRpgGameMode::SetMainUI MainProjectUserWidgets != 0"));
	}

	// RootのWBP
	{
		FString AssetPath = TEXT("/Game/Project/UI/Blueprints/Rpg/Main/WBP_RpgMainRoot.WBP_RpgMainRoot_C");
		TSubclassOf<class UUserWidget> WidgetClass;
		WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
		if (!WidgetClass)
		{
			UE_LOG(LogTemp, Log, TEXT("widget load failure"));
			return;
		}

		TObjectPtr<UProjectUserWidget> RootWidget = CreateWidget<UProjectUserWidget>(GetWorld(), WidgetClass);
		if (RootWidget)
		{
			RootWidget->AddToViewport(20);
			RootWidget->AddUserWidgetSubsytem();
			MainProjectUserWidgets.Add(RootWidget);
		}
	}

	/*
	// Main WBP
	{
		FString AssetPath = TEXT("/Game/Project/UI/Blueprints/Rpg/Main/WBP_RpgMain.WBP_RpgMain_C");
		TSubclassOf<class UUserWidget> WidgetClass;
		WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
		if (!WidgetClass)
		{
			UE_LOG(LogTemp, Log, TEXT("widget load failure"));
			return;
		}

		TObjectPtr<URpgMainUserWidget> MainWidget = CreateWidget<URpgMainUserWidget>(GetWorld(), WidgetClass);
		if (MainWidget)
		{
			RpgMainWidget = MainWidget;
			MainWidget->AddToViewport(20);
			MainWidget->AddUserWidgetSubsytem();

			MainWidget->Set();
			if (BattleManager)
			{
				MainWidget->SetState(BattleManager.Get()->GetState());
			}
			MainWidget->GetClickNextButtonDelegate().BindLambda([this]
			{
				RpgMainOnClickNextButton();
			});

			MainProjectUserWidgets.Add(MainWidget);
		}
	}
	*/

	// RpgMainViewUserWidget
	{

		// /Script/UMGEditor.WidgetBlueprint'/Game/Project/UI/Blueprints/Rpg/Main/WBP_RpgMainView.WBP_RpgMainView'
		//RpgMainViewUserWidget

		FString AssetPath = TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Project/UI/Blueprints/Rpg/Main/WBP_RpgMainView.WBP_RpgMainView_C'");
		TSubclassOf<class UUserWidget> WidgetClass;
		WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
		if (!WidgetClass)
		{
			UE_LOG(LogTemp, Log, TEXT("widget load failure"));
			return;
		}

		TObjectPtr<URpgMainViewUserWidget> MainWidget = CreateWidget<URpgMainViewUserWidget>(GetWorld(), WidgetClass);
		if (MainWidget)
		{
			RpgMainViewUserWidget = MainWidget;
			MainWidget->AddToViewport(20);
			MainWidget->AddUserWidgetSubsytem();

			MainWidget->GetClickNextButtonDelegate().BindLambda([this]
			{
				RpgMainViewOnClickNextButton();
			});

			MainWidget->GetClickTurnEndButtonDelegate().BindLambda([this]
			{
				RpgMainViewOnClickTurnEndButton();
			});

			MainWidget->GetClickCardEnemyInfoDelegate().BindLambda([this](TObjectPtr<UCdCharacterBase> Enemy, TObjectPtr<URpgCardEnemyInfoUserWidget> Widget)
			{
				RpgMainViewOnClickCardEnemyInfoDelegate(Enemy, Widget);
			});

			// プレイヤー情報更新
			UpdatePlayerInfo();
			// 敵情報更新
			UpdateEnemyInfo();
			// ProcessState更新
			UpdateProcessState(BattleManager.Get()->GetState());

			MainProjectUserWidgets.Add(MainWidget);
		}

	}



}

void AProjectRpgGameMode::CleanupMainUI()
{
}

void AProjectRpgGameMode::InitializeBattleManager()
{
	BattleManager = NewObject<URpgBattleManager>();
	check(BattleManager);

	BattleManager.Get()->GetChangePlayerInfoDelegate().BindLambda([this]
	{
		BattleManagerOnChangePlayerInfo();
	});

	BattleManager.Get()->GetChangeEnemyInfoDelegate().BindLambda([this]
	{
		BattleManagerOnChangeEnemyInfo();
	});

	BattleManager.Get()->GetChangeProcessStateDelegate().BindLambda([this](ERpgBattleProcessState State)
	{
		BattleManagerOnChangeProcessState(State);
	});


	CardList = NewObject<UActionCardList>();
	check(CardList);

	// 強制GC
	GEngine->ForceGarbageCollection(true);
}

void AProjectRpgGameMode::RpgMainViewOnClickNextButton()
{
	check(BattleManager);

	ERpgBattleProcessState Before = BattleManager.Get()->GetState();
	BattleManager.Get()->NextState();
	ERpgBattleProcessState After = BattleManager.Get()->GetState();

	OutputStateLog(Before, After);

	if (After == ERpgBattleProcessState::PlayerActionAfter)
	{
		// ウィジェットの選択状態の解除
		check(RpgMainViewUserWidget);
		RpgMainViewUserWidget.Get()->SetAllEnemyUnselected();
	}
}

void AProjectRpgGameMode::RpgMainViewOnClickTurnEndButton()
{
	check(BattleManager);

	ERpgBattleProcessState Before = BattleManager.Get()->GetState();
	BattleManager.Get()->EndPlayerTurn();
	ERpgBattleProcessState After = BattleManager.Get()->GetState();

	OutputStateLog(Before, After);
}

void AProjectRpgGameMode::RpgMainViewOnClickCardEnemyInfoDelegate(TObjectPtr<UCdCharacterBase> Enemy, TObjectPtr<URpgCardEnemyInfoUserWidget> Widget)
{
	check(BattleManager);
	if (!BattleManager.Get()->IsEnableSelectEnemy())
	{
		// 選択できるタイミングではないので何もしない
		UE_LOG(LogTemp, Log, TEXT("AProjectRpgGameMode::RpgMainViewOnClickCardEnemyInfoDelegate Not Select Timing"));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("AProjectRpgGameMode::RpgMainViewOnClickCardEnemyInfoDelegate"));

	// 選択可能な敵の数
	int32 SelectableNum = BattleManager.Get()->GetSelectableEnemyNum();

	// 対象のウィジェットは選択状態か
	if (RpgMainViewUserWidget.Get()->IsEnemySelected(Widget))
	{
		// 選択解除はほぼ無条件でOK
		RpgMainViewUserWidget.Get()->SetEnemyUnselected(Widget);
		BattleManager.Get()->OnClickEnemyInfo(Enemy, false);
		return;
	}

	// 選択可能数 > 今選択されている数
	if (SelectableNum > RpgMainViewUserWidget.Get()->GetEnemySelecatedNum())
	{
		// 選択状態にする
		RpgMainViewUserWidget.Get()->SetEnemySelected(Widget);
		BattleManager.Get()->OnClickEnemyInfo(Enemy, true);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Unselectable Enable:%d Selected:%d"), SelectableNum, RpgMainViewUserWidget.Get()->GetEnemySelecatedNum());
	}
}

void AProjectRpgGameMode::BattleManagerOnChangePlayerInfo()
{
	UpdatePlayerInfo();
}

void AProjectRpgGameMode::BattleManagerOnChangeEnemyInfo()
{
	UpdateEnemyInfo();
}

void AProjectRpgGameMode::BattleManagerOnChangeProcessState(ERpgBattleProcessState State)
{
	UpdateProcessState(State);
}

void AProjectRpgGameMode::UpdatePlayerInfo()
{
	check(BattleManager);
	check(RpgMainViewUserWidget);

	FString Str = FString::Printf(TEXT("%d/%d"),
		BattleManager.Get()->GetPlayerHp(), BattleManager.Get()->GetPlayerMaxHp());
	FText HpText = FText::FromString(Str);
	RpgMainViewUserWidget.Get()->SetHpText(HpText);
}

void AProjectRpgGameMode::UpdateEnemyInfo()
{
	check(BattleManager);
	check(RpgMainViewUserWidget);
	RpgMainViewUserWidget.Get()->SetEnemyView(BattleManager->GetEnemy(), BattleManager->GetEnemyActionAssociator());
}

void AProjectRpgGameMode::UpdateProcessState(ERpgBattleProcessState State)
{
	check(BattleManager);
	check(RpgMainViewUserWidget);

	FString Str = FString::Printf(TEXT("%s"), *ToText(State).ToString());
	FText Text = FText::FromString(Str);
	RpgMainViewUserWidget.Get()->SetStatusText(Text);
}

void AProjectRpgGameMode::OutputStateLog(ERpgBattleProcessState BeforeState, ERpgBattleProcessState AfterState)
{
	{
		FString LogText = TEXT("");
		LogText += ToText(BeforeState).ToString();
		LogText += TEXT(" -> ");
		// 次のステータスをログに設定
		LogText += ToText(AfterState).ToString();
		UE_LOG(LogTemp, Log, TEXT("%s"), *LogText);
	}

}

#if 0
void AProjectRpgGameMode::InitializeBattleManager()
{
	BattleManager = NewObject<URpgBattleManager>();
	check(BattleManager);

	// 強制GC
	GEngine->ForceGarbageCollection(true);
}

void AProjectRpgGameMode::RpgMainOnClickNextButton()
{
	if (bTasking)
	{
		UE_LOG(LogTemp, Log, TEXT("AProjectRpgGameMode::RpgMainOnClickNextButton tasking"));
		return;
	}
	bTasking = true;
	//UE_LOG(LogTemp, Log, TEXT("AProjectRpgGameMode::RpgMainOnClickNextButton start"));
	check(BattleManager);

	// ログ表示&次のステータスに進める
	{
		FString LogText = TEXT("Next ");
		LogText += ToString(BattleManager.Get()->GetState()).ToString();
		LogText += TEXT(" -> ");
		bool bResult = BattleManager.Get()->NextState();
		if (bResult)
		{
			// 次のステータスをログに設定
			LogText += ToString(BattleManager.Get()->GetState()).ToString();
		}
		else
		{
			// 失敗したので現在のステータスを表示するように設定
			LogText = TEXT("NextState Failure ");
			LogText += ToString(BattleManager.Get()->GetState()).ToString();
		}
		UE_LOG(LogTemp, Log, TEXT("%s"), *LogText);
		// Widget表示も更新
		RpgMainWidget->SetState(BattleManager.Get()->GetState());
	}
	bTasking = false;
	//UE_LOG(LogTemp, Log, TEXT("AProjectRpgGameMode::RpgMainOnClickNextButton end"));
}
#endif