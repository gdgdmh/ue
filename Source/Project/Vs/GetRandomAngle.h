// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EGetRandomAngleNum : uint16
{
	Min = 0				UMETA(DisplayName = "最小値", ToolTip = "0:最小値"),
	Max = 360			UMETA(DisplayName = "最大値", ToolTip = "1:最大値"),
};

/**
 * 
 */
class PROJECT_API GetRandomAngle
{
public:
	GetRandomAngle();
	~GetRandomAngle();

public:
	void SetSeed(int32 InitSeed);
	uint16 Get();
};
