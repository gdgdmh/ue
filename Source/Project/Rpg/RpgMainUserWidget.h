// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectUserWidget.h"
#include "RpgMainUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgMainUserWidget : public UProjectUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
};
