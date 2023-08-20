// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "CPPRpgActionType.h"

#include "RpgAttackParameter.h"
#include "RpgDefenceParameter.h"

#include "RpgActionParameter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgActionParameter : public UObject
{
	GENERATED_BODY()
	
public:
	URpgActionParameter(const FObjectInitializer& ObjectInitializer);


private:
	// アクションタイプ
	CPPRpgActionType ActionType;

	UPROPERTY()
		TObjectPtr<URpgAttackParameter> AttackParameter;

	UPROPERTY()
		TObjectPtr<URpgDefenceParameter> DefenceParameter; 
};
