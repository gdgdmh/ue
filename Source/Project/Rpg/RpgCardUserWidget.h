// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectUserWidget.h"
#include "RpgCardUserWidget.generated.h"

// Delegate
// �����ꂽ�Ƃ���Delegate
DECLARE_DELEGATE(FRpgCardUserWidgetOnClickDelegate)

/**
 * 
 */
UCLASS()
class PROJECT_API URpgCardUserWidget : public UProjectUserWidget
{
	GENERATED_BODY()
	
public:
	
	URpgCardUserWidget(const FObjectInitializer& ObjectInitializer);

	void SetId(int32 UserId);
	int32 GetId() const;

public:
	UFUNCTION(BlueprintCallable)
		void OnClick();

public:
	FRpgCardUserWidgetOnClickDelegate& GetOnClickDelegate();

public:

	FRpgCardUserWidgetOnClickDelegate CardUserWidgetOnClickDelegate;

	// ���[�U�[��`��Id
	UPROPERTY()
		int32 Id;
};
