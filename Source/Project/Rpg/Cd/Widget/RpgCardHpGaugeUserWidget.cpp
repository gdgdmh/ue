// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgCardHpGaugeUserWidget.h"

URpgCardHpGaugeUserWidget::URpgCardHpGaugeUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	HpText = FText::FromString(TEXT("20/20"));
}

void URpgCardHpGaugeUserWidget::SetHpText(FText Text)
{
	HpText = Text;
}