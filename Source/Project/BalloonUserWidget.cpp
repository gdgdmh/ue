// Fill out your copyright notice in the Description page of Project Settings.


#include "BalloonUserWidget.h"


void UBalloonUserWidget::NativeConstruct()
{
	UE_LOG(LogTemp, Log, TEXT("UBalloonUserWidget::NativeConstruct"));
	bIsSelected = false;



	FString Str = TEXT("あいう");
	Text = FText::FromString(Str);
}

void UBalloonUserWidget::OnClicked()
{
	UE_LOG(LogTemp, Log, TEXT("UBalloonUserWidget::OnClicked"));
	SetString(TEXT("くり"));
}

void UBalloonUserWidget::SetString(const FString& Txt)
{
	Text = FText::FromString(Txt);
}

void UBalloonUserWidget::SetText(const FText& Txt)
{
	Text = Txt;
}

void UBalloonUserWidget::SetData()
{
	UE_LOG(LogTemp, Log, TEXT("UBalloonUserWidget::SetData"));
	FString Str = TEXT("てす");
	Text = FText::FromString(Str);
}
