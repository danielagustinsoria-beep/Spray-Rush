// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DeathmatchPlayerState.generated.h"

UCLASS()
class SPRAY_RUSH_API ADeathmatchPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Paredes pintadas por este jugador (replicado a todos).
	UPROPERTY(ReplicatedUsing = OnRep_PaintedWalls, BlueprintReadOnly, Category = "Score")
	int32 PaintedWalls = 0;

	// true si el jugador lleva una lata equipada (lo muestra el HUD).
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Score")
	bool bHasCan = false;

	// Color asignado por el GameMode al entrar.
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Score")
	FLinearColor PlayerColor = FLinearColor::White;

	// Solo el servidor modifica estos valores.
	void AddPaintedWall();
	void SetHasCan(bool bNewHasCan);

	UFUNCTION()
	void OnRep_PaintedWalls();
};