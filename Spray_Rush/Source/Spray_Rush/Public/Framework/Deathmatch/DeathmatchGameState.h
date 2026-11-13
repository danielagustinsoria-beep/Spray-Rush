// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "DeathmatchGameState.generated.h"

/**
 * Estado de partida (Lobby / Jugando / Fin) = MatchState de AGameMode:
 * WaitingToStart / InProgress / WaitingPostMatch.
 */
UCLASS()
class SPRAY_RUSH_API ADeathmatchGameState : public AGameState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Segundos restantes de la ronda. Solo lo modifica el servidor.
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Match")
	int32 RemainingTime = 0;

	// Ganador de la partida. nullptr = empate o partida sin terminar.
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Match")
	TObjectPtr<APlayerState> WinnerPlayerState = nullptr;
};