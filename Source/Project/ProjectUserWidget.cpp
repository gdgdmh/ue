// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectUserWidget.h"
#include "VsUserWidgetSubsystem.h"

UProjectUserWidget::UProjectUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UProjectUserWidget::AddUserWidgetSubsytem()
{
	if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		if (TObjectPtr<UVsUserWidgetSubsystem> VsUserWidgetSubsystem = GameInstance->GetSubsystem<UVsUserWidgetSubsystem>())
		{
			VsUserWidgetSubsystem->Add(this);
		}
	}
}

void UProjectUserWidget::RemoveUserWidgetSubsystem()
{
	if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		if (TObjectPtr<UVsUserWidgetSubsystem> VsUserWidgetSubsystem = GameInstance->GetSubsystem<UVsUserWidgetSubsystem>())
		{
			VsUserWidgetSubsystem->Remove(this);
		}
	}
}
