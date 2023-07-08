// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectRpgGameMode.h"
#include "Rpg/RpgCharaInfo.h"
#include "ScrollTestUserWidget.h" // Test

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

	{
		FString AssetPath = TEXT("/Game/Project/UI/Blueprints/Rpg/Title/WBP_RpgTitleRoot.WBP_RpgTitleRoot_C");
		//FString AssetPath = TEXT("/Game/Project/UI/Blueprints/Rpg/WBP_RpgRoot.WBP_RpgRoot_C");
		//FString AssetPath = TEXT("/Game/Project/UI/Blueprints/WBP_ScrollTest.WBP_ScrollTest_C");
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
		}
	}

	// 
	{
		FString AssetPath = TEXT("/Game/Project/UI/Blueprints/Rpg/Title/WBP_RpgTitle.WBP_RpgTitle_C");
		TSubclassOf<class UUserWidget> WidgetClass;
		WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
		if (!WidgetClass)
		{
			UE_LOG(LogTemp, Log, TEXT("widget load failure"));
			return;
		}

		TObjectPtr<UProjectUserWidget> TitleWidget = CreateWidget<UProjectUserWidget>(GetWorld(), WidgetClass);
		if (TitleWidget)
		{
			TitleWidget->AddToViewport(20);
			TitleWidget->AddUserWidgetSubsytem();
		}

	}

}
