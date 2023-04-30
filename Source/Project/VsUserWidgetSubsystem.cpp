// Fill out your copyright notice in the Description page of Project Settings.


#include "VsUserWidgetSubsystem.h"
#include "VsWorldSettings.h"

UVsUserWidgetSubsystem::UVsUserWidgetSubsystem()
{
}

bool UVsUserWidgetSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Super::ShouldCreateSubsystem(Outer))
	{
		return false;
	}
	// WorldSetting上で使用フラグが立っていたら生成する
	if (UGameInstance* GameInstance = Cast<UGameInstance>(Outer))
	{
		if (AVsWorldSettings* VsWorldSettings = Cast<AVsWorldSettings>(GameInstance->GetWorldContext()->World()->GetWorldSettings()))
		{
			return VsWorldSettings->bUseVsUserWidgetSubsystem;
		}
	}
	return false;
}

void UVsUserWidgetSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Log, TEXT("UVsUserWidgetSubsystem::Initialize"));

}

void UVsUserWidgetSubsystem::Deinitialize()
{
	Clear();

	Super::Deinitialize();
	UE_LOG(LogTemp, Log, TEXT("UVsUserWidgetSubsystem::Deinitialize"));
}

void UVsUserWidgetSubsystem::Add(TObjectPtr<UVsUserWidget> VsUserWidget)
{
	VsUserWidgets.Add(VsUserWidget);
}

void UVsUserWidgetSubsystem::Remove(TObjectPtr<UVsUserWidget> VsUserWidget)
{
	VsUserWidgets.Remove(VsUserWidget);
}

void UVsUserWidgetSubsystem::Clear()
{
	VsUserWidgets.Empty();
}