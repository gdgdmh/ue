// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollTestUserWidget.h"
#include "BalloonUserWidget.h"

void UScrollTestUserWidget::NativeConstruct()
{
	UE_LOG(LogTemp, Log, TEXT("UScrollTestUserWidget::NativeConstruct"));

	// 動的にボタンを追加
#if 1
	FString AssetPath = TEXT("/Game/Project/UI/Blueprints/WBP_Balloon.WBP_Balloon_C");
	TSubclassOf<class UUserWidget> WidgetClass;
	WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
	if (!WidgetClass)
	{
		UE_LOG(LogTemp, Log, TEXT("WBP_Balloon widget load failure"));
		return;
	}

	TObjectPtr<UBalloonUserWidget> ScrollTest = CreateWidget<UBalloonUserWidget>(GetWorld(), WidgetClass);
	if (ScrollTest)
	{
		ScrollTest->AddToViewport(20);
		ScrollTest->AddUserWidgetSubsytem();

		DynamicScrollBox->AddChild(ScrollTest);
	}
#endif


/*
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

*/

	//DynamicScrollBox->AddChild();

}

void UScrollTestUserWidget::OnEventUserScrolled()
{
	UE_LOG(LogTemp, Log, TEXT("UScrollTestUserWidget::OnEventUserScrolled"));
}