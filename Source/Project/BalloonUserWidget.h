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
	UFUNCTION(BlueprintCallable)
		void OnClicked();

	UFUNCTION(BlueprintCallable)
		void SetString(const FString& Txt);

	UFUNCTION(BlueprintCallable)
		void SetText(const FText& Txt);

	void SetData();

public:
	UPROPERTY(BlueprintReadWrite)
		FText Text;

private:
	bool bIsSelected;


};
