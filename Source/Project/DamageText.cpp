// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageText.h"

UDamageText::UDamageText(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetWidgetType(EVsUserWidgetType::DamageText);
}


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
	AnimationFinishDelegate.BindUFunction(this, "EventAnimationFinish");
	BindToAnimationEvent(TransparentAnimation, AnimationFinishDelegate, EWidgetAnimationEvent::Finished);

	PlayAnimation(TransparentAnimation);
}

void UDamageText::EventAnimationFinish()
{
	UE_LOG(LogTemp, Log, TEXT("EventAnimationFinish"));
	RemoveUserWidgetSubsystem();
}
