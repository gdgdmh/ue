// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionCardDefenceParameter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UActionCardDefenceParameter : public UObject
{
	GENERATED_BODY()
	
public:
	UActionCardDefenceParameter(const FObjectInitializer& ObjectInitializer);

public:
	void SetPawer(int32 Power);
	int32 GetPower() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DefencePower;

};
