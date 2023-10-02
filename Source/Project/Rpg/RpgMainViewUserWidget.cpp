// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgMainViewUserWidget.h"



void FEnemyDisplayInfo::SetCharacter(TObjectPtr<UCdCharacterBase> EnemyData)
{
	Enemy = EnemyData;
}

void FEnemyDisplayInfo::SetUserWidget(TObjectPtr<URpgCardEnemyInfoUserWidget> Widget)
{
	UserWidget = Widget;
}

TObjectPtr<UCdCharacterBase> FEnemyDisplayInfo::GetEnemy()
{
	return Enemy;
}

const TObjectPtr<UCdCharacterBase> FEnemyDisplayInfo::GetEnemy() const
{
	return Enemy;
}

TObjectPtr<URpgCardEnemyInfoUserWidget> FEnemyDisplayInfo::GetUserWidget()
{
	return UserWidget;
}

const TObjectPtr<URpgCardEnemyInfoUserWidget> FEnemyDisplayInfo::GetUserWidget() const
{
	return UserWidget;
}

bool FEnemyDisplayInfo::IsSameCharacter(const TObjectPtr<UCdCharacterBase>& EnemyData) const
{
	if (Enemy == EnemyData)
	{
		return true;
	}
	return false;
}

bool FEnemyDisplayInfo::IsSameUserWidget(const TObjectPtr<URpgCardEnemyInfoUserWidget>& Widget) const
{
	if (UserWidget == Widget)
	{
		return true;
	}
	return false;
}

bool FEnemyDisplayInfo::IsDead() const
{
	return Enemy->GetParameter()->IsDead();
}

void FEnemyDisplayInfo::SetWidgetHp()
{
	UserWidget->SetHp(Enemy->GetParameter()->GetHp(), Enemy->GetParameter()->GetMaxHp());
}

void FEnemyDisplayInfo::DeadWidget()
{
	UserWidget->GetOnClickDelegate().Unbind();
	UserWidget->Hide();
}

void FEnemyDisplayInfos::Add(const FEnemyDisplayInfo& Info)
{
	Infos.Add(Info);
}

void FEnemyDisplayInfos::Remove(int32 Index)
{
	const int32 Size = Infos.Num();
	if (Index <= Size)
	{
		// Indexの範囲外指定された
		UE_LOG(LogTemp, Log, TEXT("FEnemyDisplayInfos::Remove Index Range error Index:%d Range:%d"), Index, Size);
		check(false);
		return;
	}

	Infos.RemoveAt(Index);
}

bool FEnemyDisplayInfos::Find(const TObjectPtr<UCdCharacterBase>& Target)
{
	for (const auto& Info : Infos)
	{
		if (Info.IsSameCharacter(Target))
		{
			return true;
		}
	}
	return false;
}

int32 FEnemyDisplayInfos::FindAt(const TObjectPtr<UCdCharacterBase>& Target)
{
	// 一致してるオブジェクトのindexを返す(見つからないときは-1)
	const int32 Size = Infos.Num();
	for (int32 i = 0; i < Size; ++i)
	{
		if (Infos[i].IsSameCharacter(Target))
		{
			return i;
		}
	}
	return -1;
}

void FEnemyDisplayInfos::FindEnemy(TObjectPtr<UCdCharacterBase>& Enemy, const TObjectPtr<URpgCardEnemyInfoUserWidget> Widget)
{
	Enemy = nullptr;
	const int32 Size = Infos.Num();
	for (int32 i = 0; i < Size; ++i)
	{
		if (Infos[i].IsSameUserWidget(Widget))
		{
			Enemy = Infos[i].GetEnemy();
			return;
		}
	}

}

FEnemyDisplayInfo& FEnemyDisplayInfos::At(int32 Index)
{
	const int32 Size = Infos.Num();
	if ((Index < 0) || (Index >= Size))
	{
		// Indexの範囲外指定された
		UE_LOG(LogTemp, Log, TEXT("FEnemyDisplayInfos::At Index Range error Index:%d Range:%d"), Index, Size);
		check(false);
		return Infos[0];
	}
	return Infos[Index];
}

const FEnemyDisplayInfo& FEnemyDisplayInfos::At(int32 Index) const
{
	const int32 Size = Infos.Num();
	if ((Index < 0) || (Index >= Size))
	{
		// Indexの範囲外指定された
		UE_LOG(LogTemp, Log, TEXT("FEnemyDisplayInfos::At Index Range error Index:%d Range:%d"), Index, Size);
		check(false);
		return Infos[0];
	}
	return Infos[Index];
}

URpgMainViewUserWidget::URpgMainViewUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FRpgMainViewClickNextButtonDelegate& URpgMainViewUserWidget::GetClickNextButtonDelegate()
{
	return ClickNextButtonDelegate;
}

FRpgMainViewClickTurnEndButtonDelegate& URpgMainViewUserWidget::GetClickTurnEndButtonDelegate()
{
	return ClickTurnEndButtonDelegate;
}

FRpgCardEnemyInfoUserWidgetClickDelegate& URpgMainViewUserWidget::GetClickCardEnemyInfoDelegate()
{
	return ClickCardEnemyInfoDelegate;
}

void URpgMainViewUserWidget::NativeConstruct()
{
}

void URpgMainViewUserWidget::SetHpText(FText Text)
{
	PlayerInfo.Get()->SetHpText(Text);
}

void URpgMainViewUserWidget::SetEnemyView(const TArray<TObjectPtr<UCdCharacterBase> >& Enemies)
{
	// オブジェクト自体追加されているか なかったら追加
	{
		for (const auto& Enemy : Enemies)
		{
			if (EnemyDisplayInfos.Find(Enemy))
			{
				// すでにある
				continue;
			}
			if (Enemy->GetParameter()->IsDead())
			{
				// 死亡している
				continue;
			}

			// viewに追加
			{
				FString AssetPath = TEXT("/Game/Project/UI/Blueprints/Rpg/Main/Card/WBP_RpgCardEnemyInfo.WBP_RpgCardEnemyInfo_C");
				TSubclassOf<class UUserWidget> TempWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*AssetPath)).LoadSynchronous();
				if (!TempWidgetClass)
				{
					UE_LOG(LogTemp, Log, TEXT("URpgMainViewUserWidget::SetEnemyView widget load failure"));
					return;
				}
				TObjectPtr<URpgCardEnemyInfoUserWidget> Widget = CreateWidget<URpgCardEnemyInfoUserWidget>(GetWorld(), TempWidgetClass);
				if (!Widget)
				{
					continue;
				}
				Widget->AddToViewport();
				Widget->AddUserWidgetSubsytem();
				Widget->GetOnClickDelegate().BindLambda([this](TObjectPtr<URpgCardEnemyInfoUserWidget> UserWidget)
				{
					TObjectPtr<UCdCharacterBase> Enemy = nullptr;
					EnemyDisplayInfos.FindEnemy(Enemy, UserWidget);
					check(Enemy);

					GetClickCardEnemyInfoDelegate().ExecuteIfBound(Enemy, UserWidget);
				});

				EnemyArea->AddChild(Widget);

				// Widgetの初期化
				Widget->SetHp(Enemy->GetParameter()->GetHp(), Enemy->GetParameter()->GetMaxHp());
				// 選択状態はoff
				Widget->HideSelectFrame();

				// displayinfoに追加
				FEnemyDisplayInfo Info;
				Info.SetCharacter(Enemy);
				Info.SetUserWidget(Widget);
				EnemyDisplayInfos.Add(Info);
			}
		}
	}

	// 既存の敵の更新
	for (int32 i = 0; i < EnemyDisplayInfos.Size(); ++i)
	{
		FEnemyDisplayInfo& Info = EnemyDisplayInfos.At(i);
		// 死んでいるなら更新しない
		if (Info.IsDead())
		{
			// 非表示
			Info.DeadWidget();
			continue;
		}
		// HP反映
		Info.SetWidgetHp();
	}
}

// 敵が選択されたとき
void URpgMainViewUserWidget::OnSelectEnemyInfo(TObjectPtr<URpgCardEnemyInfoUserWidget> Widget)
{
	// 選択可能数と現在選択されている敵に合わせて選択を調整
}

// 選択状態か
bool URpgMainViewUserWidget::IsEnemySelected(const TObjectPtr<URpgCardEnemyInfoUserWidget> Widget) const
{
	check(Widget);
	return Widget->IsShowingSelectFrame();
}

// 選択状態にする
void URpgMainViewUserWidget::SetEnemySelected(TObjectPtr<URpgCardEnemyInfoUserWidget> Widget)
{
	Widget->ShowSelectFrame();
}
// 非選択状態にする
void URpgMainViewUserWidget::SetEnemyUnselected(TObjectPtr<URpgCardEnemyInfoUserWidget> Widget)
{
	Widget->HideSelectFrame();
}

void URpgMainViewUserWidget::SetAllEnemyUnselected()
{
	int32 Size = EnemyDisplayInfos.Size();
	for (int32 i = 0; i < Size; ++i)
	{
		TObjectPtr<URpgCardEnemyInfoUserWidget> EnemyWidget = EnemyDisplayInfos.At(i).GetUserWidget();
		check(EnemyWidget);
		EnemyWidget->HideSelectFrame();
	}

}

// いくつ選択状態になっているか
int32 URpgMainViewUserWidget::GetEnemySelecatedNum() const
{
	int32 num = 0;
	for (int32 i = 0; i < EnemyDisplayInfos.Size(); ++i)
	{
		const auto& Info = EnemyDisplayInfos.At(i);
		check(Info.GetUserWidget());
		if (Info.GetUserWidget().Get()->IsShowingSelectFrame())
		{
			++num;
		}
	}
	return num;
}

void URpgMainViewUserWidget::OnClickTurnEndButton()
{
	// Delegate呼び出し
	ClickTurnEndButtonDelegate.ExecuteIfBound();
}

void URpgMainViewUserWidget::OnClickNextButton()
{
	// Delegate呼び出し
	ClickNextButtonDelegate.ExecuteIfBound();
}
