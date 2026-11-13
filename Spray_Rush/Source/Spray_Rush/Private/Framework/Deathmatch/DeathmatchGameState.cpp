// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/Deathmatch/DeathmatchGameState.h"

#include "Net/UnrealNetwork.h"

void ADeathmatchGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADeathmatchGameState, RemainingTime);
	DOREPLIFETIME(ADeathmatchGameState, WinnerPlayerState);
}