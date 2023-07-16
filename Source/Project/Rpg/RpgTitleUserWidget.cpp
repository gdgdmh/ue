// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgTitleUserWidget.h"

void URpgTitleUserWidget::NativeConstruct()
{
}

void URpgTitleUserWidget::OnClickedEventStartButton()
{
	UE_LOG(LogTemp, Log, TEXT("URpgTitleUserWidget::OnClickedEventStartButton"));

	RpgTitleDelegate.ExecuteIfBound(ERpgTitleUserWidgetSelectType::Start);

	//BindToAnimationEvent(TransparentAnimation, AnimationFinishDelegate, EWidgetAnimationEvent::Finished);
}

void URpgTitleUserWidget::OnClickedEventTestButton()
{
	UE_LOG(LogTemp, Log, TEXT("URpgTitleUserWidget::OnClickedEventTestButton"));
}
























