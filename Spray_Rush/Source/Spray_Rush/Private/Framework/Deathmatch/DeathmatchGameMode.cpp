// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Deathmatch/DeathmatchGameMode.h"
#include "Framework/Deathmatch/DeathmatchPlayerController.h"

ADeathmatchGameMode::ADeathmatchGameMode()
{
	//PlayerControllerClass = ADeathmatchPlayerController::StaticClass();
	bDelayedStart = true;
	
}

void ADeathmatchGameMode::StartMatch()
{
	Super::StartMatch();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("Empezó la partida"));
}

void ADeathmatchGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(MatchStartTimer, this, &ADeathmatchGameMode::StartMatch, MatchStartTimeDuration, false);
}

void ADeathmatchGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
