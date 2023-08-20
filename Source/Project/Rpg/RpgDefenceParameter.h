// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "CPPRpgTargetType.h"

#include "RpgDefenceParameter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API URpgDefenceParameter : public UObject
{
	GENERATED_BODY()
	
public:
	URpgDefenceParameter(const FObjectInitializer& ObjectInitializer);

private:
	// 対象
	CPPRpgTargetType TargetType;
};
