// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgCardUserWidget.h"

URpgCardUserWidget::URpgCardUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void URpgCardUserWidget::OnClick()
{
	UE_LOG(LogTemp, Log, TEXT("URpgCardUserWidget::OnClick"));
	CardUserWidgetOnClickDelegate.ExecuteIfBound();
}

FRpgCardUserWidgetOnClickDelegate& URpgCardUserWidget::GetOnClickDelegate()
{
	return CardUserWidgetOnClickDelegate;
}

//void URpgCardUserWidget::SetId(int32 UserId)
//{
//	Id = UserId;
//}

//int32 URpgCardUserWidget::GetId() const
//{
//	return Id;
//}


