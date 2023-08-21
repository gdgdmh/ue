// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "RpgActionParameter.h"

#include "ActionCard.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UActionCard : public UObject
{
	GENERATED_BODY()
	
public:
	UActionCard(const FObjectInitializer& ObjectInitializer);


protected:
	// アクションパラメーター
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TObjectPtr<URpgActionParameter> ActionParameter;

};
