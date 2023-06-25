// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjectUserWidget.h"
#include "DamageText.generated.h"

DECLARE_DELEGATE(FDamageTextAnimationFinishDelegate)

//class PROJECT_API UDamageText : public UUserWidget


/**
 * 
 */
UCLASS()
class PROJECT_API UDamageText : public UProjectUserWidget
{
	GENERATED_BODY()
	
public:
	UDamageText(const FObjectInitializer& ObjectInitializer);

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

	void Test();


	UFUNCTION(BlueprintCallable)
		void EventAnimationFinish();
	/*
UFUNCTION(BlueprintCallable, Category = "Test")
		void TestEvent() { UE_LOG(LogTemp, Log, TEXT("TestEvent!")); }
	*/

public:
	UPROPERTY(BlueprintReadWrite)
		FString DamageText;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
		TObjectPtr<UWidgetAnimation> TransparentAnimation;

	FWidgetAnimationDynamicEvent AnimationFinishDelegate;
};
