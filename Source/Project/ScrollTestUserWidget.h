// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/ProjectUserWidget.h"
#include "BalloonUserWidget.h"
#include "Components/ScrollBox.h"
#include "Engine/DataTable.h"
#include "ScrollTestUserWidget.generated.h"


USTRUCT(BlueprintType)
struct FScrollTestDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FScrollTestDataTable()
	{
		Rank = 0;
		Name = FText::FromString("");
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Rank;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;
};

/**
 * 
 */
UCLASS()
class PROJECT_API UScrollTestUserWidget : public UProjectUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	void Set();

	void Clear();

public:

	UFUNCTION(BlueprintCallable)
		void OnEventUserScrolled();

private:
	
	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UScrollBox> ScrollBoxTest;

	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UScrollBox> DynamicScrollBox;

	UPROPERTY()
		TArray< TObjectPtr<UBalloonUserWidget> > BalloonUserWidgets;

	UPROPERTY()
		TArray<FScrollTestDataTable> TestDataTables;
};
