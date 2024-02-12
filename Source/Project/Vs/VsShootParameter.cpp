// Fill out your copyright notice in the Description page of Project Settings.


#include "VsShootParameter.h"

AVsShootParameter::AVsShootParameter()
{
}

AVsShootParameter::~AVsShootParameter()
{
}

void AVsShootParameter::Copy(AVsShootParameter* Parameter)
{
	check(Parameter != nullptr);
	Location = Parameter->Location;
	Rotation = Parameter->Rotation;
	SpawnParameters = Parameter->SpawnParameters;
}
void AVsShootParameter::SetLocation(FVector LocationValue)
{
	this->Location = LocationValue;
}

void AVsShootParameter::SetRotation(FRotator RotationValue)
{
	this->Rotation = RotationValue;
}

void AVsShootParameter::SetSpawnParameters(FActorSpawnParameters SpawnParametersValue)
{
	this->SpawnParameters = SpawnParametersValue;
}

const FVector AVsShootParameter::GetLocation() const
{
	return Location;
}

const FRotator AVsShootParameter::GetRotation() const
{
	return Rotation;
}

const FActorSpawnParameters AVsShootParameter::GetSpawnParameters() const
{
	return SpawnParameters;
}
