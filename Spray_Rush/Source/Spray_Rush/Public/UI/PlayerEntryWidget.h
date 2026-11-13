// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerEntryWidget.generated.h"

class UImage;
class UTextBlock;

/**
 * "Miniatura" de un jugador en el HUD: cuadro de color, nombre,
 * paredes pintadas (X / objetivo) e icono de lata.
 * El layout se arma en el Blueprint hijo (WBP_PlayerEntry).
 */
UCLASS()
class SPRAY_RUSH_API UPlayerEntryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetData(const FString& PlayerName, int32 Walls, int32 Goal, const FLinearColor& Color, bool bHasCan);

protected:
    // Los nombres deben coincidir EXACTO con los widgets del Blueprint.
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ColorImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> NameText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> WallsText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> CanIcon;
};
