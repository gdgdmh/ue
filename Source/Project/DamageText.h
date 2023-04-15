// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageText.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UDamageText : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
		void SetText(const FString& Text);


	void SetPosition(float PosX, float PosY);

	UFUNCTION(BlueprintCallable)
		const FString& GetText() const;

	UFUNCTION(BlueprintCallable)
		void PlayTransparentAnimation();

public:
	UPROPERTY(BlueprintReadWrite)
		FString DamageText;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
		TObjectPtr<UWidgetAnimation> TransparentAnimation;
};
