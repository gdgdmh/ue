// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VsUserWidget.h"
#include "Components/Button.h"
#include "TitleUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UTitleUserWidget : public UVsUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void OnClickedEvent();

public:
	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UButton> ButtonPattern1;

	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UButton> ButtonPattern2;

};
