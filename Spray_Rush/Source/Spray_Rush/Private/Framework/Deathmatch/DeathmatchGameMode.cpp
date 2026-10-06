// Fill out your copyright notice in the Description page of Project Settings.


#include "Deathmatch/DeathmatchGameMode.h"
#include "Deathmatch/DeathmatchPlayerController.h"

ADeathmatchGameMode::ADeathmatchGameMode()
{
	PlayerControllerClass = ADeathmatchPlayerController::StaticClass();
}
