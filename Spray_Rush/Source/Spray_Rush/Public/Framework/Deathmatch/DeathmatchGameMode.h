// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DeathmatchGameMode.generated.h"

class APaintableGraffiti;
class ADeathmatchPlayerState;
class APlayerState;

UCLASS()
class SPRAY_RUSH_API ADeathmatchGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ADeathmatchGameMode();

	virtual void StartMatch() override;

	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	// Lo llama la pared (solo servidor) despues de sumar el punto.
	void WallPainted(ADeathmatchPlayerState* Painter);

	FTimerHandle MatchStartTimer;
	FTimerHandle RoundTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Gamemode", meta = (ClampMin = "0.1"))
	float MatchStartTimeDuration = 5.f;

	// Duracion de la ronda en segundos.
	UPROPERTY(EditDefaultsOnly, Category = "Gamemode", meta = (ClampMin = "1"))
	int32 RoundDuration = 60;

	UPROPERTY(BlueprintReadOnly, Category = "Gamemode")
	TArray<TObjectPtr<APaintableGraffiti>> PaintableGraffitis;

	UPROPERTY(EditDefaultsOnly, Category = "Gamemode")
	int32 ObjectivePaints = 3;

protected:
	void TickRound();
	void CheckWinCondition(ADeathmatchPlayerState* Painter);
	void FinishMatch(APlayerState* Winner);

private:
	int32 NextColorIndex = 0;
};