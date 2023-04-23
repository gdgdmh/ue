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
	AnimationFinishDelegate.BindUFunction(this, "EventAnimationFinish");
	BindToAnimationEvent(TransparentAnimation, AnimationFinishDelegate, EWidgetAnimationEvent::Finished);

	PlayAnimation(TransparentAnimation);
}

void UDamageText::Test()
{
	//FWidgetAnimationDynamicEvent Delegate;
	//Delegate.BindUFunction();
	//Delegate.
	//BindToAnimationEvent(TransparentAnimation, AnimationFinishDelegate, EWidgetAnimationEvent::Finished);


/*
FWidgetAnimationDynamicEvent Delegate;
EWidgetAnimationEvent Event;
UserWidget->BindToAnimationEvent(UserWidget->TransparentAnimation, Delegate, );

*/
	
}

void UDamageText::EventAnimationFinish()
{
	UE_LOG(LogTemp, Log, TEXT("EventAnimationFinish"));
}

#if 0
FWidgetAnimationDynamicEvent Delegate;
EWidgetAnimationEvent Event;
UserWidget->BindToAnimationEvent(UserWidget->TransparentAnimation, Delegate, );

#endif


