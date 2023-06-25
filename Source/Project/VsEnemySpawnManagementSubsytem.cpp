// Fill out your copyright notice in the Description page of Project Settings.


#include "VsEnemySpawnManagementSubsytem.h"
#include "VsWorldSettings.h"

UVsEnemySpawnManagementSubsytem::UVsEnemySpawnManagementSubsytem()
{
}

bool UVsEnemySpawnManagementSubsytem::ShouldCreateSubsystem(UObject* Outer) const
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
			return VsWorldSettings->bUseEnemySpawnSubsystem;
		}
	}
	return false;
}

void UVsEnemySpawnManagementSubsytem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Log, TEXT("UVsEnemySpawnManagementSubsytem::Initialize"));
	bIsActive = false;
	SpawnVsEnemy = GetWorld()->SpawnActor<ASpawnVsEnemy>();
	SpawnEnemyManager = GetWorld()->SpawnActor<ASpawnEnemyManager>();
	SpawnEnemyManager->SetFirstTimer(0.1f);
	Start(GetWorld()->GetTimerManager());
}

void UVsEnemySpawnManagementSubsytem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogTemp, Log, TEXT("UVsEnemySpawnManagementSubsytem::Deinitialize"));
}

void UVsEnemySpawnManagementSubsytem::Start(FTimerManager& TimerManager)
{
	bIsActive = true;
	StartTimer(TimerManager);
}

void UVsEnemySpawnManagementSubsytem::StartTimer(FTimerManager& TimerManager)
{
	UE_LOG(LogTemp, Log, TEXT("UVsEnemySpawnManagementSubsytem::StartTimer"));
	TimerManager.SetTimer(TimerHandle, this, &UVsEnemySpawnManagementSubsytem::OnTimerElapsed, SpawnEnemyManager->GetNextTimer(), false);
}

void UVsEnemySpawnManagementSubsytem::OnTimerElapsed()
{
	UE_LOG(LogTemp, Log, TEXT("UVsEnemySpawnManagementSubsytem::OnTimerElapsed"));
	SpawnEnemyManager->ProcessSpawn();

	StartTimer(GetWorld()->GetTimerManager());
}
