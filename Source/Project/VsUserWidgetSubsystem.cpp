// Fill out your copyright notice in the Description page of Project Settings.


#include "VsUserWidgetSubsystem.h"
#include "ProjectWorldSettings.h"

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
		if (AProjectWorldSettings* ProjectWorldSettings = Cast<AProjectWorldSettings>(GameInstance->GetWorldContext()->World()->GetWorldSettings()))
		{
			return ProjectWorldSettings->bUseUserWidgetSubsystem;
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

void UVsUserWidgetSubsystem::Add(TObjectPtr<UProjectUserWidget> ProjectUserWidget)
{
	VsUserWidgets.Add(ProjectUserWidget);
}

void UVsUserWidgetSubsystem::Remove(TObjectPtr<UProjectUserWidget> ProjectUserWidget)
{
	VsUserWidgets.Remove(ProjectUserWidget);
}

void UVsUserWidgetSubsystem::Clear()
{
	VsUserWidgets.Empty();
}