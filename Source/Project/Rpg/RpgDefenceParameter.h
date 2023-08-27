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

	void SetTargetType(CPPRpgTargetType Target) { TargetType = Target; }
	void SetDefencePower(int32 Power) { DefencePower = Power; }

	CPPRpgTargetType GetTargetType() const { return TargetType; }
	int32 GetDefencePower() const { return DefencePower; }

public:
	// 対象
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		CPPRpgTargetType TargetType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 DefencePower;
};
