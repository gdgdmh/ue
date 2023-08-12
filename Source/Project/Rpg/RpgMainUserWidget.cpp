// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgMainUserWidget.h"

#include "RpgCharaInfo.h"

void URpgMainUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!AllyArea)
	{
		UE_LOG(LogTemp, Log, TEXT("URpgMainUserWidget::NativeConstruct null"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("URpgMainUserWidget::NativeConstruct not null"));
	}
}

void URpgMainUserWidget::OnClickedNextButton()
{
	UE_LOG(LogTemp, Log, TEXT("URpgMainUserWidget::OnClickedNextButton"));
	// Delegate呼び出し
	ClickNextButtonDelegate.ExecuteIfBound();
}

void URpgMainUserWidget::Set()
{
	for (int32 i = 0; i < 2; ++i)
	{
		CreateCharaInfoWidget();
	}
	SetDummyCharaInfoParam();
	SetState(ERpgBattleProcessState::None);
}

void URpgMainUserWidget::SetState(ERpgBattleProcessState State)
{
	// ERpgBattleProcessStateを文字列に変換して設定
	StateText = ToString(State);
}

void URpgMainUserWidget::CreateCharaInfoWidget()
{
	FString AssetPath = TEXT("/Game/Project/UI/Blueprints/Rpg/Main/WBP_RpgCharaInfo.WBP_RpgCharaInfo_C");
	TSubclassOf<class UUserWidget> WidgetClass;
	WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
	if (!WidgetClass)
	{
		UE_LOG(LogTemp, Log, TEXT("widget load failure"));
		return;
	}
	TWeakObjectPtr<URpgCharaInfo> Info = CreateWidget<URpgCharaInfo>(GetWorld(), WidgetClass);
	if ((Info.IsValid()) && (AllyArea))
	{
		AllyArea->AddChild(Info.Get());
		Info->AddUserWidgetSubsytem();

		RpgCharaInfos.Add(Info);
	}
}

void URpgMainUserWidget::SetDummyCharaInfoParam()
{
	if (RpgCharaInfos.Num() != 2)
	{
		return;
	}

	if (RpgCharaInfos[0].IsValid())
	{
		TWeakObjectPtr<URpgCharaInfo>& Info = RpgCharaInfos[0];
		FText Name = FText::FromString(TEXT("キャラ1"));
		Info.Get()->SetName(Name);
		Info.Get()->SetHp(30);
		Info.Get()->SetSp(10);
		{
			FText Status = FText::FromString(TEXT("なし"));
			Info.Get()->SetSt(Status);
		}
	}
	if (RpgCharaInfos[1].IsValid())
	{
		TWeakObjectPtr<URpgCharaInfo>& Info = RpgCharaInfos[1];
		FText Name = FText::FromString(TEXT("キャラ2"));
		Info.Get()->SetName(Name);
		Info.Get()->SetHp(31);
		Info.Get()->SetSp(12);
		{
			FText Status = FText::FromString(TEXT("なし"));
			Info.Get()->SetSt(Status);
		}
	}
}
