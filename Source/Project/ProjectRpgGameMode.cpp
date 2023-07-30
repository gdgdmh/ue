// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectRpgGameMode.h"
#include "Rpg/RpgCharaInfo.h"
#include "Rpg/RpgTitleUserWidget.h"
#include "Rpg/RpgMainUserWidget.h"

#include "Rpg/RpgBattlePartyFactory.h"


AProjectRpgGameMode::AProjectRpgGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = APawn::StaticClass();
	//PlayerControllerClass = AMatch3PlayerController::StaticClass();
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
	// 初期化
	{
		TWeakObjectPtr<URpgBattlePartyFactory> Factory = NewObject<URpgBattlePartyFactory>();
		AllyParty = Factory->Create(ERpgBattlePartyFactoryType::Test);
		EnemyParty = Factory->Create(ERpgBattlePartyFactoryType::TestEnemy);
	}

	if (MainProjectUserWidgets.Num() != 0)
	{
		// 初期化前に0以外なのはおかしい
		UE_LOG(LogTemp, Log, TEXT("AProjectRpgGameMode::SetMainUI MainProjectUserWidgets != 0"));
	}

	///Script/UMGEditor.WidgetBlueprint'/Game/Project/UI/Blueprints/Rpg/Main/WBP_RpgMainRoot.WBP_RpgMainRoot'

	///Script/UMGEditor.WidgetBlueprint'/Game/Project/UI/Blueprints/Rpg/Main/WBP_RpgMain.WBP_RpgMain'

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
			MainWidget->AddToViewport(20);
			MainWidget->AddUserWidgetSubsytem();
			MainProjectUserWidgets.Add(MainWidget);
		}

	}
}

void AProjectRpgGameMode::CleanupMainUI()
{
}
