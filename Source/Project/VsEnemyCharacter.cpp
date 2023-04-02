// Fill out your copyright notice in the Description page of Project Settings.


#include "VsEnemyCharacter.h"
#include "Blueprint/UserWidget.h"

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

float AVsEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	//UE_LOG(LogTemp, Log, TEXT("%f"), DamageAmount);
	SubHealthFloat(DamageAmount);
	ShowDamage(DamageAmount);
	return Health;
}

void AVsEnemyCharacter::SubHealth(int32 sub)
{
	Health -= sub;
	NormalizationHealth();
}

void AVsEnemyCharacter::SubHealthFloat(float sub)
{
	int32 damage = static_cast<float>(sub);
	SubHealth(damage);
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
		CheckDestroy();
	}
}

void AVsEnemyCharacter::CheckDestroy()
{
	if (bIsAlive)
	{
		return;
	}
	Destroy();
}

void AVsEnemyCharacter::ShowDamage(float DamageAmount)
{
	UE_LOG(LogTemp, Log, TEXT("%f"), DamageAmount);
	FString AssetPath = TEXT("/Game/Project/UI/Blueprints/WBP_Damage.WBP_Damage_C");

	TSubclassOf<class UUserWidget> WidgetClass;
	WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
	if (!WidgetClass)
	{
		UE_LOG(LogTemp, Log, TEXT("ShowDamage widget load failure"));
		return;
	}

	UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	if (UserWidget)
	{
		UserWidget->AddToViewport();
		// ‚¤‚Ü‚­‚¢‚©‚È‚¢
		/*
		FVector2D Trans(100, 100);
		FVector2D Scale;
		FVector2D Shear;
		FWidgetTransform Transform(Trans, Scale, Shear, 0.0f);
		UserWidget->SetRenderTransform(Transform);
		UserWidget->AddToViewport();
		*/
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ShowDamage failure"));
	}
}