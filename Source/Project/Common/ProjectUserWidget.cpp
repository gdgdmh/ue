// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectUserWidget.h"
#include "UserWidgetSubsystem.h"

UProjectUserWidget::UProjectUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UProjectUserWidget::AddUserWidgetSubsytem()
{
	if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		if (TObjectPtr<UUserWidgetSubsystem> VsUserWidgetSubsystem = GameInstance->GetSubsystem<UUserWidgetSubsystem>())
		{
			VsUserWidgetSubsystem->Add(this);
		}
	}
}

void UProjectUserWidget::RemoveUserWidgetSubsystem()
{
	if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		if (TObjectPtr<UUserWidgetSubsystem> VsUserWidgetSubsystem = GameInstance->GetSubsystem<UUserWidgetSubsystem>())
		{
			VsUserWidgetSubsystem->Remove(this);
		}
	}
}

void UProjectUserWidget::ShowObject()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UProjectUserWidget::HideObject()
{
	SetVisibility(ESlateVisibility::Hidden);
}

bool UProjectUserWidget::IsShowing() const
{
	return IsInViewport();
}
