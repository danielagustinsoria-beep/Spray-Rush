// Fill out your copyright notice in the Description page of Project Settings.


#include "Deathmatch/DeathmatchPlayerController.h"

#include "EnhancedInputSubsystems.h"

void ADeathmatchPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			// 2. Verificar que la variable del IMC no sea nula y vincularlo
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, MappingPriority);
			}
		}
	}
}
