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
	// Delegate呼び出し
	ClickTurnEndButtonDelegate.ExecuteIfBound();
}

void URpgMainViewUserWidget::OnClickNextButton()
{
	// Delegate呼び出し
	ClickNextButtonDelegate.ExecuteIfBound();
}
