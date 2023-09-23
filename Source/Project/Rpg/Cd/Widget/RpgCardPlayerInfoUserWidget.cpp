// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgCardPlayerInfoUserWidget.h"

void URpgCardPlayerInfoUserWidget::SetHpText(FText Text)
{
	check(HpGauge);
	HpGauge.Get()->SetHpText(Text);
}