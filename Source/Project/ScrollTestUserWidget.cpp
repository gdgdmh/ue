// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollTestUserWidget.h"
#include "BalloonUserWidget.h"

void UScrollTestUserWidget::NativeConstruct()
{
	UE_LOG(LogTemp, Log, TEXT("UScrollTestUserWidget::NativeConstruct"));
	Super::NativeConstruct();
	Set();
}

void UScrollTestUserWidget::Set()
{
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

	TObjectPtr<UBalloonUserWidget> Balloon = CreateWidget<UBalloonUserWidget>(GetWorld(), WidgetClass);
	if (Balloon)
	{
		
		Balloon->AddToViewport(20);
		Balloon->AddUserWidgetSubsytem();
		DynamicScrollBox->AddChild(Balloon);
		// このタイミングで初期化しないとNativeConstructが呼ばれてしまうことがあるので適用されない
		Balloon->SetData();
	}
#endif

}

void UScrollTestUserWidget::OnEventUserScrolled()
{
	UE_LOG(LogTemp, Log, TEXT("UScrollTestUserWidget::OnEventUserScrolled"));
}