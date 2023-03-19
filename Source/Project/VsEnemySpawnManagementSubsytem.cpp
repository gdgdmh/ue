// Fill out your copyright notice in the Description page of Project Settings.


#include "VsEnemySpawnManagementSubsytem.h"

UVsEnemySpawnManagementSubsytem::UVsEnemySpawnManagementSubsytem()
{
}

bool UVsEnemySpawnManagementSubsytem::ShouldCreateSubsystem(UObject* Outer) const
{
	// ��������true�ɂ���
	// ���������I�ɂ͏����ɉ�����true�ɂ��Ȃ��ƑS���̃��x���Ő�������邽�߁A����
	return true;
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
