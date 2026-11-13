// Fill out your copyright notice in the Description page of Project Settings.
 
#include "Framework/Deathmatch/DeathmatchGameMode.h"
 
#include "Engine/Engine.h"
#include "Framework/Deathmatch/DeathmatchGameState.h"
#include "Framework/Deathmatch/DeathmatchPlayerState.h"
 
ADeathmatchGameMode::ADeathmatchGameMode()
{
    bDelayedStart = true;
 
    // Valores por defecto (los Class Defaults del Blueprint tienen prioridad si los cambiaste).
    GameStateClass = ADeathmatchGameState::StaticClass();
    PlayerStateClass = ADeathmatchPlayerState::StaticClass();
}
 
void ADeathmatchGameMode::BeginPlay()
{
    Super::BeginPlay();
 
    GetWorldTimerManager().SetTimer(MatchStartTimer, this, &ADeathmatchGameMode::StartMatch,
        FMath::Max(MatchStartTimeDuration, 0.1f), false);
}
 
void ADeathmatchGameMode::StartMatch()
{
    if (HasMatchStarted()) return;
 
    Super::StartMatch();
 
    if (ADeathmatchGameState* GS = GetGameState<ADeathmatchGameState>())
    {
        GS->RemainingTime = RoundDuration;
    }
    GetWorldTimerManager().SetTimer(RoundTimer, this, &ADeathmatchGameMode::TickRound, 1.f, true);
 
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("Empezó la partida"));
}
 
void ADeathmatchGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
 
    if (ADeathmatchPlayerState* PS = Cast<ADeathmatchPlayerState>(NewPlayer->PlayerState))
    {
        static const FLinearColor Colors[] = { FLinearColor::Red, FLinearColor::Blue, FLinearColor::Green, FLinearColor::Yellow };
        PS->PlayerColor = Colors[NextColorIndex++ % 4];
    }
}
 
void ADeathmatchGameMode::TickRound()
{
    ADeathmatchGameState* GS = GetGameState<ADeathmatchGameState>();
    if (!GS || !IsMatchInProgress()) return;
 
    GS->RemainingTime = FMath::Max(0, GS->RemainingTime - 1);
    if (GS->RemainingTime > 0) return;
 
    // Tiempo agotado: gana quien tenga mas paredes. Si hay empate, no hay ganador.
    ADeathmatchPlayerState* Best = nullptr;
    bool bTie = false;
    for (APlayerState* PS : GS->PlayerArray)
    {
        ADeathmatchPlayerState* DPS = Cast<ADeathmatchPlayerState>(PS);
        if (!DPS) continue;
 
        if (!Best || DPS->PaintedWalls > Best->PaintedWalls)
        {
            Best = DPS;
            bTie = false;
        }
        else if (DPS->PaintedWalls == Best->PaintedWalls)
        {
            bTie = true;
        }
    }
 
    const bool bHasWinner = Best && !bTie && Best->PaintedWalls > 0;
    FinishMatch(bHasWinner ? Best : nullptr);
}
 
void ADeathmatchGameMode::WallPainted(ADeathmatchPlayerState* Painter)
{
    FString Message = FString::Printf(TEXT("Painted Walls: %d"), Painter->PaintedWalls);
    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, Message);
    
    CheckWinCondition(Painter);
}
 
void ADeathmatchGameMode::CheckWinCondition(ADeathmatchPlayerState* Painter)
{
    if (Painter && Painter->PaintedWalls >= ObjectivePaints)
    {
        FinishMatch(Painter);
    }
}
 
void ADeathmatchGameMode::FinishMatch(APlayerState* Winner)
{
    if (!IsMatchInProgress()) return;
 
    GetWorldTimerManager().ClearTimer(RoundTimer);
 
    if (ADeathmatchGameState* GS = GetGameState<ADeathmatchGameState>())
    {
        GS->WinnerPlayerState = Winner;
    }
 
    EndMatch(); // MatchState pasa a WaitingPostMatch ("Fin").
}