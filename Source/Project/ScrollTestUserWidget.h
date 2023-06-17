// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VsUserWidget.h"
#include "Components/ScrollBox.h"
#include "Engine/DataTable.h"
#include "ScrollTestUserWidget.generated.h"


USTRUCT(BlueprintType)
struct FScrollTestDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Rank;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;
};

/**
 * 
 */
UCLASS()
class PROJECT_API UScrollTestUserWidget : public UVsUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	void Set();

public:

	UFUNCTION(BlueprintCallable)
		void OnEventUserScrolled();

private:
	
	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UScrollBox> ScrollBoxTest;

	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UScrollBox> DynamicScrollBox;

	UPROPERTY()
		TArray<FScrollTestDataTable> TestDataTables;
};
