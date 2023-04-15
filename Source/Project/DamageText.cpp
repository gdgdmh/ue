// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageText.h"


void UDamageText::SetText(const FString& Text)
{
	DamageText = Text;
}

void UDamageText::SetPosition(float PosX, float PosY)
{
	SetPositionInViewport(FVector2D(PosX, PosY));
}

const FString& UDamageText::GetText() const
{
	return DamageText;
}

void UDamageText::PlayTransparentAnimation()
{
	PlayAnimation(TransparentAnimation);
}
