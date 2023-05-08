// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPPVsUserWidgetType.h"
#include "VsUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UVsUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UVsUserWidget(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintCallable)
	void AddUserWidgetSubsytem();

	UFUNCTION(BlueprintCallable)
	void RemoveUserWidgetSubsystem();

	void SetWidgetType(EVsUserWidgetType Type) { VsUserWidgetType = Type; }
	EVsUserWidgetType GetWidgetType() const { return VsUserWidgetType; }

private:
	EVsUserWidgetType VsUserWidgetType = EVsUserWidgetType::None;
};
