// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgCardEnemyInfoUserWidget.h"

void URpgCardEnemyInfoUserWidget::OnClick()
{
	EnemyInfoUserWidgetOnClickDelegate.ExecuteIfBound(this);
}

void URpgCardEnemyInfoUserWidget::SetHpText(FText Text)
{
	check(HpGauge);
	HpGauge.Get()->SetHpText(Text);
}

void URpgCardEnemyInfoUserWidget::SetHp(int32 Hp, int32 MaxHp)
{
	FString Str = FString::Printf(TEXT("%d/%d"), Hp, MaxHp);
	FText HpText = FText::FromString(Str);
	SetHpText(HpText);
}

void URpgCardEnemyInfoUserWidget::Hide()
{
	HideObject();
}

void URpgCardEnemyInfoUserWidget::HideSelectFrame()
{
	check(SelectFrame);
	SelectFrame->Hide();
}

void URpgCardEnemyInfoUserWidget::ShowSelectFrame()
{
	check(SelectFrame);
	SelectFrame->Show();
}

bool URpgCardEnemyInfoUserWidget::IsShowingSelectFrame() const
{
	check(SelectFrame);
	return SelectFrame->IsShowing();
}


FRpgCardEnemyInfoUserWidgetOnClickDelegate& URpgCardEnemyInfoUserWidget::GetOnClickDelegate()
{
	return EnemyInfoUserWidgetOnClickDelegate;
}