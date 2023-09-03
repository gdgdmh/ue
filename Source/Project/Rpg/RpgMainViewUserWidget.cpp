// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgMainViewUserWidget.h"



void FEnemyDisplayInfo::SetCharacter(TObjectPtr<UCdCharacterBase> EnemyData)
{
	Enemy = EnemyData;
}

void FEnemyDisplayInfo::SetUserWidget(TObjectPtr<URpgCardEnemyInfoUserWidget> Widget)
{
	UserWidget = Widget;
}

bool FEnemyDisplayInfo::IsSameCharacter(const TObjectPtr<UCdCharacterBase>& EnemyData) const
{
	if (Enemy == EnemyData)
	{
		return true;
	}
	return false;
}

bool FEnemyDisplayInfo::IsSameUserWidget(const TObjectPtr<URpgCardEnemyInfoUserWidget>& Widget) const
{
	if (UserWidget == Widget)
	{
		return true;
	}
	return false;
}

URpgMainViewUserWidget::URpgMainViewUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FRpgMainViewClickNextButtonDelegate& URpgMainViewUserWidget::GetClickNextButtonDelegate()
{
	return ClickNextButtonDelegate;
}

FRpgMainViewClickTurnEndButtonDelegate& URpgMainViewUserWidget::GetClickTurnEndButtonDelegate()
{
	return ClickTurnEndButtonDelegate;
}

void URpgMainViewUserWidget::NativeConstruct()
{
}

void URpgMainViewUserWidget::SetHpText(FText Text)
{
	PlayerInfo.Get()->SetHpText(Text);
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
