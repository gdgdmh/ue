// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VsUserWidget.h"
#include "Components/ScrollBox.h"
#include "ScrollTestUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UScrollTestUserWidget : public UVsUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
		void OnEventUserScrolled();

private:
	
	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UScrollBox> ScrollBoxTest;

};
