// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VsUserWidget.h"
#include "BalloonUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBalloonUserWidget : public UVsUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void OnClicked();

private:
	bool bIsSelected;

};
