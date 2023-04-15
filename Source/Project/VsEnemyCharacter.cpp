// Fill out your copyright notice in the Description page of Project Settings.


#include "VsEnemyCharacter.h"
#include "Blueprint/UserWidget.h"
#include "DamageText.h"
#include "Engine/DamageEvents.h"


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

	// ÉqÉbÉgÇÃè⁄ç◊ÇéÊìæ
	FVector Position;
	{
		FHitResult HitResult;
		FVector OutImpulseDir;
		DamageEvent.GetBestHitInfo(this, DamageCauser, HitResult, OutImpulseDir);
		Position.X = HitResult.ImpactPoint.X;
		Position.Y = HitResult.ImpactPoint.Y;
		Position.Z = HitResult.ImpactPoint.Z;
	}

	SubHealthFloat(DamageAmount);
	ShowDamage(DamageAmount, Position);


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

void AVsEnemyCharacter::ShowDamage(float DamageAmount, FVector Position)
{
	UE_LOG(LogTemp, Log, TEXT("%f"), DamageAmount);



	//FString AssetPath = TEXT("/Game/Project/UI/Blueprints/WBP_DamageText.WBP_DamageText_C");
	//TSubclassOf<class DamageText> WidgetClass;
	//WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();

	//FString path = "/Game/Title/TitleWidgetBlueprint.TitleWidgetBlueprint_C";

#if 0
	UDamageText* DmgText = CreateWidget<UDamageText>(GetWorld(), UDamageText::StaticClass());
	if (DmgText)
	{
		DmgText->AddToViewport();
	}
#endif

#if 1
	FString AssetPath = TEXT("/Game/Project/UI/Blueprints/WBP_DamageText.WBP_DamageText_C");
	TSubclassOf<class UUserWidget> WidgetClass;
	WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
	if (!WidgetClass)
	{
		UE_LOG(LogTemp, Log, TEXT("ShowDamage widget load failure"));
		return;
	}

	UDamageText* UserWidget = CreateWidget<UDamageText>(GetWorld(), WidgetClass);
	if (UserWidget)
	{
		int32 Damage = static_cast<int32>(DamageAmount);
		UserWidget->SetText(FString::FromInt(Damage));
		UserWidget->SetPosition(100, 100);
		UserWidget->PlayTransparentAnimation();
		UserWidget->AddToViewport();



		// çÌèúÇ∑ÇÈç€ÇÕ
		//RemoveFromViewport

		// Ç§Ç‹Ç≠Ç¢Ç©Ç»Ç¢
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
#endif
}