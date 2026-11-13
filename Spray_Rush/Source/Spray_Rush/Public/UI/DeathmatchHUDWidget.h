// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeathmatchHUDWidget.generated.h"

class UPanelWidget;
class UPlayerEntryWidget;
class UTextBlock;

/**
 * HUD de la partida: tiempo restante, una "miniatura" por jugador y pantalla final.
 * Lee GameState y PlayerState (ya replicados) unas 5 veces por segundo.
 */
UCLASS()
class SPRAY_RUSH_API UDeathmatchHUDWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    // Los nombres deben coincidir EXACTO con los widgets del Blueprint.
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TimerText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ResultText;

    // Cualquier contenedor (Vertical Box, Horizontal Box...).
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UPanelWidget> PlayersBox;

    UPROPERTY(EditDefaultsOnly, Category = "HUD")
    TSubclassOf<UPlayerEntryWidget> PlayerEntryClass;

    // Objetivo de paredes que se muestra en cada tarjeta (X / WallsGoal).
    UPROPERTY(EditDefaultsOnly, Category = "HUD")
    int32 WallsGoal = 5;

private:
    void Refresh();

    float TimeSinceRefresh = 0.f;
};
