// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common/ProjectUserWidget.h"
#include "RpgCharaInfo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgCharaInfo : public UProjectUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void SetName(const FText& Name);
	void SetHp(int32 Hp);
	void SetSp(int32 Sp);
	void SetSt(const FText& Text);

	// bind
public:
	
	UPROPERTY(BlueprintReadWrite)
		FText NameText;

	UPROPERTY(BlueprintReadWrite)
		FText HpText;

	UPROPERTY(BlueprintReadWrite)
		FText SpText;

	UPROPERTY(BlueprintReadWrite)
		FText StText;
};
