// Fill out your copyright notice in the Description page of Project Settings.


#include "NextActionUserWidget.h"

UNextActionUserWidget::UNextActionUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UNextActionUserWidget::Set(ECdEnemyActionType Type)
{
	// 一旦全部を非表示にする
	TArray<ECdEnemyActionType> TypeArray =
	{
		ECdEnemyActionType::Attack,
		ECdEnemyActionType::Defence,
		ECdEnemyActionType::Buff,
		ECdEnemyActionType::Debuff,
		ECdEnemyActionType::Unknown,
	};
	for (auto HideType : TypeArray)
	{
		SetIconDisplay(HideType, false);
	}
	SetIconDisplay(Type, true);
}

void UNextActionUserWidget::SetIconDisplay(ECdEnemyActionType Type, bool Display)
{
	switch (Type)
	{
	case ECdEnemyActionType::None:
		break;
	case ECdEnemyActionType::Attack:
		if (!AttackIconImage.Get())
		{
			return;
		}
		if (Display)
		{
			AttackIconImage->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			AttackIconImage->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	case ECdEnemyActionType::Defence:
		if (!DefenceIconImage.Get())
		{
			return;
		}
		if (Display)
		{
			DefenceIconImage->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			DefenceIconImage->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	case ECdEnemyActionType::Buff:
		if (!BuffIconImage.Get())
		{
			return;
		}
		if (Display)
		{
			BuffIconImage->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			BuffIconImage->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	case ECdEnemyActionType::Debuff:
		if (!DebuffIconImage.Get())
		{
			return;
		}
		if (Display)
		{
			DebuffIconImage->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			DebuffIconImage->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	case ECdEnemyActionType::Unknown:
		if (!UnknownIconImage.Get())
		{
			return;
		}
		if (Display)
		{
			UnknownIconImage->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			UnknownIconImage->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	default:
		// ハンドリングされてないタイプ
		check(false);
		break;
	}
}