// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgMainViewUserWidget.h"





FRpgMainViewClickNextButtonDelegate& URpgMainViewUserWidget::GetClickNextButtonDelegate()
{
	return ClickNextButtonDelegate;
}

FRpgMainViewClickTurnEndButtonDelegate& URpgMainViewUserWidget::GetClickTurnEndButtonDelegate()
{
	return ClickTurnEndButtonDelegate;
}

void URpgMainViewUserWidget::OnClickTurnEndButton()
{
	// DelegateåƒÇ—èoÇµ
	ClickTurnEndButtonDelegate.ExecuteIfBound();
}

void URpgMainViewUserWidget::OnClickNextButton()
{
	// DelegateåƒÇ—èoÇµ
	ClickNextButtonDelegate.ExecuteIfBound();
}
