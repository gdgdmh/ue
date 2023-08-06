// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectUserWidget.h"
#include "Components/HorizontalBox.h"
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

public:
	void Set();

protected:
	void CreateCharaInfoWidget();
	void SetDummyCharaInfoParam();

public:
	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UHorizontalBox> AllyArea;

	UPROPERTY()
		TArray<TWeakObjectPtr<URpgCharaInfo> > RpgCharaInfos;
};
