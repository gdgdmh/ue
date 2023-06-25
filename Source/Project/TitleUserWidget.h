// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectUserWidget.h"
#include "Components/Button.h"
#include "TitleUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UTitleUserWidget : public UProjectUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:

	UFUNCTION(BlueprintCallable)
		void OnClickedEventButtonPattern1();

	UFUNCTION(BlueprintCallable)
		void OnClickedEventButtonPattern2();

public:
	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UButton> ButtonPattern1;

	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UButton> ButtonPattern2;

};

#if 0

FString AssetPath = TEXT("/Game/Project/UI/Blueprints/WBP_DamageText.WBP_DamageText_C");
TSubclassOf<class UUserWidget> WidgetClass;
WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
if (!WidgetClass)
{
	UE_LOG(LogTemp, Log, TEXT("ShowDamage widget load failure"));
	return;
}

TObjectPtr<UDamageText> DamageText = CreateWidget<UDamageText>(GetWorld(), WidgetClass);
if (DamageText)
{
	int32 Damage = static_cast<int32>(DamageAmount);
	DamageText->SetText(FString::FromInt(Damage));
	DamageText->SetPosition(Position.X, Position.Y);
	DamageText->PlayTransparentAnimation();
	DamageText->AddToViewport();
	DamageText->AddUserWidgetSubsytem();


	// 削除する際は
	//RemoveFromViewport

	// うまくいかない
	/*
	FVector2D Trans(100, 100);
	FVector2D Scale;
	FVector2D Shear;
	FWidgetTransform Transform(Trans, Scale, Shear, 0.0f);
	UserWidget->SetRenderTransform(Transform);
	UserWidget->AddToViewport();
	*/
}
else
{
	UE_LOG(LogTemp, Log, TEXT("ShowDamage failure"));
}

#endif
