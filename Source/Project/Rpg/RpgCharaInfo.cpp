// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgCharaInfo.h"

void URpgCharaInfo::NativeConstruct()
{
	Super::NativeConstruct();
}

void URpgCharaInfo::SetName(const FText& Name)
{
	NameText = Name;
}

void URpgCharaInfo::SetHp(int32 Hp)
{
	FString HpString = FString::Printf(TEXT("%d"), Hp);
	HpText = FText::FromString(HpString);
}

void URpgCharaInfo::SetSp(int32 Sp)
{
	FString SpString = FString::Printf(TEXT("%d"), Sp);
	SpText = FText::FromString(SpString);
}

void URpgCharaInfo::SetSt(const FText& Text)
{
	StText = Text;
}
