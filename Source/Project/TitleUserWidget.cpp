// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleUserWidget.h"
#include "ScrollTestUserWidget.h"


void UTitleUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Log, TEXT("UTitleUserWidget::NativeConstruct"));

	///Script/UMGEditor.WidgetBlueprint'/Game/Project/UI/Blueprints/WBP_ScrollTest.WBP_ScrollTest'
	//D:/data/git/ue/Content/Project/UI/Blueprints/WBP_ScrollTest.uasset

	FString AssetPath = TEXT("/Game/Project/UI/Blueprints/WBP_ScrollTest.WBP_ScrollTest_C");
	TSubclassOf<class UUserWidget> WidgetClass;
	WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
	if (!WidgetClass)
	{
		UE_LOG(LogTemp, Log, TEXT("ShowDamage widget load failure"));
		return;
	}

	TObjectPtr<UScrollTestUserWidget> ScrollTest = CreateWidget<UScrollTestUserWidget>(GetWorld(), WidgetClass);
	if (ScrollTest)
	{
		ScrollTest->AddToViewport(20);
		ScrollTest->AddUserWidgetSubsytem();
	}
	/*
	TObjectPtr<UDamageText> ScrollTest = CreateWidget<UDamageText>(GetWorld(), WidgetClass);
	if (DamageText)
	{
	}
	*/


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

#endif

}

void UTitleUserWidget::OnClickedEventButtonPattern1()
{
	UE_LOG(LogTemp, Log, TEXT("OnClickedEventButtonPattern1"));
}

void UTitleUserWidget::OnClickedEventButtonPattern2()
{
	UE_LOG(LogTemp, Log, TEXT("OnClickedEventButtonPattern2"));
}
