// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common/ProjectUserWidget.h"
#include "RpgCardUserWidget.generated.h"

// Delegate
// 押されたときのDelegate
DECLARE_DELEGATE(FRpgCardUserWidgetOnClickDelegate)

/**
 * カードWidget
 */
UCLASS()
class PROJECT_API URpgCardUserWidget : public UProjectUserWidget
{
	GENERATED_BODY()
	
public:
	
	URpgCardUserWidget(const FObjectInitializer& ObjectInitializer);

	//void SetId(int32 UserId);
	//int32 GetId() const;

public:
	UFUNCTION(BlueprintCallable)
		void OnClick();

public:
	FRpgCardUserWidgetOnClickDelegate& GetOnClickDelegate();

public:

	FRpgCardUserWidgetOnClickDelegate CardUserWidgetOnClickDelegate;

	// ユーザー定義のId
	//UPROPERTY()
	//	int32 Id;
};
