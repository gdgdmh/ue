// Fill out your copyright notice in the Description page of Project Settings.


#include "VsEnemyCharacter.h"


AVsEnemyCharacter::AVsEnemyCharacter()
{
	MaxHealth = 1;
	Health = MaxHealth;
	bIsAlive = true;
}

void AVsEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AVsEnemyCharacter::SubHealth(int32 sub)
{
	Health -= sub;
	NormalizationHealth();
}

void AVsEnemyCharacter::AddHealth(int32 add)
{
	Health += add;
	NormalizationHealth();
}

bool AVsEnemyCharacter::IsAlive() const
{
	return bIsAlive;
}

void AVsEnemyCharacter::NormalizationHealth()
{
	check(Health <= MaxHealth);
	check(MaxHealth != 0);
	if (Health > MaxHealth)
	{
		Health = MaxHealth;
	}
	if (Health < 0)
	{
		Health = 0;
		bIsAlive = false;
	}
}