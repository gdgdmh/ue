// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgCardEnemyInfoUserWidget.h"

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