// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/PlayerEntryWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UPlayerEntryWidget::SetData(const FString& PlayerName, int32 Walls, int32 Goal, const FLinearColor& Color, bool bHasCan)
{
    if (ColorImage) ColorImage->SetColorAndOpacity(Color);
    if (NameText) NameText->SetText(FText::FromString(PlayerName));
    if (WallsText) WallsText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), Walls, Goal)));
    if (CanIcon) CanIcon->SetVisibility(bHasCan ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
}
