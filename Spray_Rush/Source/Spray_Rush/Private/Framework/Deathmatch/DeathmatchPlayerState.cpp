// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/Deathmatch/DeathmatchPlayerState.h"

#include "Net/UnrealNetwork.h"

void ADeathmatchPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADeathmatchPlayerState, PaintedWalls);
	DOREPLIFETIME(ADeathmatchPlayerState, bHasCan);
	DOREPLIFETIME(ADeathmatchPlayerState, PlayerColor);
}

void ADeathmatchPlayerState::AddPaintedWall()
{
	if (!HasAuthority()) return;

	++PaintedWalls;
	OnRep_PaintedWalls(); // El host no recibe el RepNotify solo: se llama a mano.
}

void ADeathmatchPlayerState::SetHasCan(bool bNewHasCan)
{
	if (!HasAuthority()) return;

	bHasCan = bNewHasCan;
}

void ADeathmatchPlayerState::OnRep_PaintedWalls()
{
	UE_LOG(LogTemp, Log, TEXT("%s lleva %d paredes pintadas"), *GetPlayerName(), PaintedWalls);
}