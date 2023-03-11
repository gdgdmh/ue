// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EGetRandomAngleNum : uint16
{
	Min = 0				UMETA(DisplayName = "�ŏ��l", ToolTip = "0:�ŏ��l"),
	Max = 360			UMETA(DisplayName = "�ő�l", ToolTip = "1:�ő�l"),
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
