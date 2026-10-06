// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MenuGameModeBase.h"
#include "Menu/MenuPlayerController.h"

AMenuGameModeBase::AMenuGameModeBase()
{
	// Asignar el Player Controller de menú personalizado
	PlayerControllerClass = AMenuPlayerController::StaticClass();
	
	// Opcional: no generar ningún Pawn para no capturar inputs de movimiento
	DefaultPawnClass = nullptr;
}