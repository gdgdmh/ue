// Fill out your copyright notice in the Description page of Project Settings.


#include "VsEnemySpawnManagementSubsytem.h"

UVsEnemySpawnManagementSubsytem::UVsEnemySpawnManagementSubsytem()
{
}

bool UVsEnemySpawnManagementSubsytem::ShouldCreateSubsystem(UObject* Outer) const
{
	// いったんtrueにする
	// ただ将来的には条件に応じてtrueにしないと全部のレベルで生成されるため、注意
	return true;
}

void UVsEnemySpawnManagementSubsytem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Log, TEXT("UVsEnemySpawnManagementSubsytem::Initialize"));
	bIsActive = false;
	SpawnVsEnemy = GetWorld()->SpawnActor<ASpawnVsEnemy>();
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
	const float Timer = 10.0f;
	UE_LOG(LogTemp, Log, TEXT("UVsEnemySpawnManagementSubsytem::StartTimer"));
	TimerManager.SetTimer(TimerHandle, this, &UVsEnemySpawnManagementSubsytem::OnTimerElapsed, Timer, false);
}

void UVsEnemySpawnManagementSubsytem::OnTimerElapsed()
{
	UE_LOG(LogTemp, Log, TEXT("UVsEnemySpawnManagementSubsytem::OnTimerElapsed"));
	
	// spawn
	FVector Location(950, 300, 90);
	FRotator Rotation(0, 0, 0);
	SpawnVsEnemy->Spawn(EEnemyType::Bat, Location, Rotation);

	StartTimer(GetWorld()->GetTimerManager());
}