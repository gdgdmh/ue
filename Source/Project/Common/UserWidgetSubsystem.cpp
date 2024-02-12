// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetSubsystem.h"
#include "ProjectWorldSettings.h"

UUserWidgetSubsystem::UUserWidgetSubsystem()
{
}

bool UUserWidgetSubsystem::ShouldCreateSubsystem(UObject* Outer) const
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

void UUserWidgetSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Log, TEXT("UUserWidgetSubsystem::Initialize"));

}

void UUserWidgetSubsystem::Deinitialize()
{
	Clear();

	Super::Deinitialize();
	UE_LOG(LogTemp, Log, TEXT("UUserWidgetSubsystem::Deinitialize"));
}

void UUserWidgetSubsystem::Add(TObjectPtr<UProjectUserWidget> ProjectUserWidget)
{
	VsUserWidgets.Add(ProjectUserWidget);
}

void UUserWidgetSubsystem::Remove(TObjectPtr<UProjectUserWidget> ProjectUserWidget)
{
	VsUserWidgets.Remove(ProjectUserWidget);
}

void UUserWidgetSubsystem::Clear()
{
	VsUserWidgets.Empty();
}