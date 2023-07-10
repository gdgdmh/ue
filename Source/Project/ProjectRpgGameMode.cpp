// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectRpgGameMode.h"
#include "Rpg/RpgCharaInfo.h"
#include "Rpg/RpgTitleUserWidget.h"

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
	// �^�C�g��UI���Z�b�g
	SetTitleUI();
}

void AProjectRpgGameMode::OnDelegateRpgTitleUserWidgetSelect(ERpgTitleUserWidgetSelectType Type)
{
	// �^�C�g����Delegate(�I������)
	if (Type == ERpgTitleUserWidgetSelectType::Start)
	{
		UE_LOG(LogTemp, Log, TEXT("AProjectRpgGameMode::OnDelegateRpgTitleUserWidgetSelect Start"));
		// �^�C�g��UI�̍폜
		CleanupTitleUI();
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
		// �������O��0�ȊO�Ȃ̂͂�������
		UE_LOG(LogTemp, Log, TEXT("AProjectRpgGameMode::BeginPlay TitleProjectUserWidgets != 0"));
	}

	// Root��WBP
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

	// �^�C�g�����C��WBP
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
	// �o�^�Ƃ͋t����Viewport����J��&�T�u�V�X�e������폜
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
