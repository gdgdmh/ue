// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectRpgGameMode.h"
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
		FString AssetPath = TEXT("/Game/Project/UI/Blueprints/WBP_ScrollTest.WBP_ScrollTest_C");
		TSubclassOf<class UUserWidget> WidgetClass;
		WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
		if (!WidgetClass)
		{
			UE_LOG(LogTemp, Log, TEXT("ShowDamage widget load failure"));
			return;
		}

		TObjectPtr<UScrollTestUserWidget> ScrollTest = CreateWidget<UScrollTestUserWidget>(GetWorld(), WidgetClass);
		if (ScrollTest)
		{
			ScrollTest->AddToViewport(20);
			ScrollTest->AddUserWidgetSubsytem();
		}

	}

}
