// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "ActionCard.h"

#include "ActionCardList.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UActionCardList : public UObject
{
	GENERATED_BODY()
	
public:
	UActionCardList(const FObjectInitializer& ObjectInitializer);

	void AddCard(TObjectPtr<UActionCard> Card);
	void RemoveCard(TObjectPtr<UActionCard> Card);

	// 指定されたListのカードをコピーする
	void CopyCard(UActionCardList& Source);

	TArray<TObjectPtr<UActionCard> > GetList() const;

protected:
	UPROPERTY()
		TArray<TObjectPtr<UActionCard> > Cards;
};
