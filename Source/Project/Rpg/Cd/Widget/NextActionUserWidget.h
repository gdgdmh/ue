// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Rpg/RpgCardUserWidget.h"

// image
#include "Components/Image.h"

// action type
#include "../CPPCdEnemyActionType.h"

#include "NextActionUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UNextActionUserWidget : public URpgCardUserWidget
{
	GENERATED_BODY()
	
public:
	UNextActionUserWidget(const FObjectInitializer& ObjectInitializer);

	// ����̃A�C�R���̂ݕ\������
	void Set(ECdEnemyActionType Type);

	// �ʏ킱����͊O������Ăяo���Ȃ�
	void SetIconDisplay(ECdEnemyActionType Type, bool Display);

public:
	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UImage> AttackIconImage;

	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UImage> DefenceIconImage;

	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UImage> UnknownIconImage;

	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UImage> BuffIconImage;

	UPROPERTY(Transient, meta = (BindWidget))
		TObjectPtr<UImage> DebuffIconImage;


};
