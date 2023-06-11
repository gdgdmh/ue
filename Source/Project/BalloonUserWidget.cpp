// Fill out your copyright notice in the Description page of Project Settings.


#include "BalloonUserWidget.h"


void UBalloonUserWidget::NativeConstruct()
{
	bIsSelected = false;
	//FString Str = TEXT("テスト");
	//Text = FText::FromString(Str);
	Text = TEXT("テスト");
}

void UBalloonUserWidget::OnClicked()
{
}

