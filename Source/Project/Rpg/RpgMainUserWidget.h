// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Vs/ProjectUserWidget.h"

#include "Components/HorizontalBox.h"
#include "CPPRpgBattleProcessState.h"
#include "RpgCharaInfo.h"

#include "RpgMainUserWidget.generated.h"

// Delegate
// NextButtonが押されたときのDelegate
DECLARE_DELEGATE(FRpgMainClickNextButtonDelegate)

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
	UFUNCTION(BlueprintCallable)
		void OnClickedNextButton();

public:
	void Set();

	void SetState(ERpgBattleProcessState State);

	FRpgMainClickNextButtonDelegate& GetClickNextButtonDelegate()
	{
		return ClickNextButtonDelegate;
	}

protected:
	void CreateCharaInfoWidget();
	void SetDummyCharaInfoParam();

public:
	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UHorizontalBox> AllyArea;

	UPROPERTY()
		TArray<TObjectPtr<URpgCharaInfo> > RpgCharaInfos;

	// ステータスのテキスト(プロパティはBind)
	UPROPERTY(Transient, meta = (BindWidget))
		FText StateText;

protected:
	FRpgMainClickNextButtonDelegate ClickNextButtonDelegate;

};
