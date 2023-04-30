// Fill out your copyright notice in the Description page of Project Settings.


#include "VsUserWidget.h"
#include "VsUserWidgetSubsystem.h"

UVsUserWidget::UVsUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UVsUserWidget::AddUserWidgetSubsytem()
{
	if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		if (TObjectPtr<UVsUserWidgetSubsystem> VsUserWidgetSubsystem = GameInstance->GetSubsystem<UVsUserWidgetSubsystem>())
		{
			VsUserWidgetSubsystem->Add(this);
		}
	}
}

void UVsUserWidget::RemoveUserWidgetSubsystem()
{
	if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		if (TObjectPtr<UVsUserWidgetSubsystem> VsUserWidgetSubsystem = GameInstance->GetSubsystem<UVsUserWidgetSubsystem>())
		{
			VsUserWidgetSubsystem->Remove(this);
		}
	}
}
