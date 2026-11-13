// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/DeathmatchHUDWidget.h"

#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"
#include "UI/PlayerEntryWidget.h"
#include "Framework/Deathmatch/DeathmatchGameState.h"
#include "Framework/Deathmatch/DeathmatchPlayerState.h"

void UDeathmatchHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    TimeSinceRefresh += InDeltaTime;
    if (TimeSinceRefresh >= 0.2f)
    {
        TimeSinceRefresh = 0.f;
        Refresh();
    }
}

void UDeathmatchHUDWidget::Refresh()
{
    UWorld* World = GetWorld();
    const ADeathmatchGameState* GS = World ? World->GetGameState<ADeathmatchGameState>() : nullptr;
    if (!GS) return; // El GameState puede tardar un instante en llegar al cliente.

    // Tiempo restante.
    if (TimerText)
    {
        const int32 Secs = GS->RemainingTime;
        TimerText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Secs / 60, Secs % 60)));
    }

    // Una tarjeta por jugador.
    if (PlayersBox && PlayerEntryClass)
    {
        const auto& Players = GS->PlayerArray;

        if (PlayersBox->GetChildrenCount() != Players.Num())
        {
            PlayersBox->ClearChildren();
            for (int32 i = 0; i < Players.Num(); ++i)
            {
                if (UPlayerEntryWidget* Entry = CreateWidget<UPlayerEntryWidget>(GetOwningPlayer(), PlayerEntryClass))
                {
                    PlayersBox->AddChild(Entry);
                }
            }
        }

        for (int32 i = 0; i < Players.Num(); ++i)
        {
            const ADeathmatchPlayerState* PS = Cast<ADeathmatchPlayerState>(Players[i].Get());
            UPlayerEntryWidget* Entry = Cast<UPlayerEntryWidget>(PlayersBox->GetChildAt(i));
            if (PS && Entry)
            {
                Entry->SetData(PS->GetPlayerName(), PS->PaintedWalls, WallsGoal, PS->PlayerColor, PS->bHasCan);
            }
        }
    }

    // Pantalla final: Victoria / Derrota / Empate.
    if (ResultText)
    {
        if (GS->HasMatchEnded())
        {
            FString Text;
            if (!GS->WinnerPlayerState)
            {
                Text = TEXT("Empate");
            }
            else if (GS->WinnerPlayerState == GetOwningPlayerState())
            {
                Text = TEXT("¡Victoria!");
            }
            else
            {
                Text = TEXT("Derrota");
            }
            ResultText->SetText(FText::FromString(Text));
            ResultText->SetVisibility(ESlateVisibility::HitTestInvisible);
        }
        else
        {
            ResultText->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}
