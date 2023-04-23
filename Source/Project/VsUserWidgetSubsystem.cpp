// Fill out your copyright notice in the Description page of Project Settings.


#include "VsUserWidgetSubsystem.h"

UVsUserWidgetSubsystem::UVsUserWidgetSubsystem()
{
}

bool UVsUserWidgetSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Super::ShouldCreateSubsystem(Outer))
	{
		return false;
	}
	// WorldSetting�Ƀt���O��p�ӂ���܂ł͍쐬���Ȃ�
	return false;
}

void UVsUserWidgetSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Log, TEXT("UVsUserWidgetSubsystem::Initialize"));

}

void UVsUserWidgetSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogTemp, Log, TEXT("UVsUserWidgetSubsystem::Deinitialize"));
}
