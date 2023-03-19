// Fill out your copyright notice in the Description page of Project Settings.


#include "GetRandomAngle.h"

GetRandomAngle::GetRandomAngle()
{
}

GetRandomAngle::~GetRandomAngle()
{
}

void GetRandomAngle::SetSeed(int32 InitSeed)
{
	FMath::SRandInit(InitSeed);
}

uint16 GetRandomAngle::Get()
{
	return FMath::RandRange(static_cast<uint16>(EGetRandomAngleNum::Min), static_cast<uint16>(EGetRandomAngleNum::Max));
}
