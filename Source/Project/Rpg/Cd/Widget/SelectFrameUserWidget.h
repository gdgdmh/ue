// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Common/ProjectUserWidget.h"

#include "Components/Image.h"

#include "SelectFrameUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API USelectFrameUserWidget : public UProjectUserWidget
{
	GENERATED_BODY()
	
public:
	void Hide();
	void Show();

	// bind ui object
public:
	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UImage> FrameImage;

};
