// Fill out your copyright notice in the Description page of Project Settings.


#include "Deathmatch/DeathmatchPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Characters/Character_J.h"

void ADeathmatchPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, MappingPriority);
			}
		}
	}
}

void ADeathmatchPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (IA_Jump)
		{
			EnhancedInputComponent->BindAction(
				IA_Jump, 
				ETriggerEvent::Started, 
				this, 
				&ADeathmatchPlayerController::HandleJump
			);
			UE_LOG(LogTemp, Warning, TEXT("DeathmatchPlayerController::IA_JUMP PRESSED"));
		}
		
		if (IA_Move)
		{
			EnhancedInputComponent->BindAction(
				IA_Move, 
				ETriggerEvent::Triggered, 
				this, 
				&ADeathmatchPlayerController::HandleMove
			);
			UE_LOG(LogTemp, Warning, TEXT("DeathmatchPlayerController::IA_ROTATION PRESSED"));
		}
	}
}

void ADeathmatchPlayerController::HandleJump(const FInputActionValue& Value)
{
	bool bIsJumping = Value.Get<bool>();
    
	// Este Caracter_J Se tiene que ir cuando cree más personajes. Tengo que hacerlo dinamico para que tome el personaje seleccionado.
	if (ACharacter* Character_J = Cast<ACharacter_J>(GetPawn()))
	{
		Character_J->Jump();
	}
}

void ADeathmatchPlayerController::HandleMove(const FInputActionValue& Value)
{

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn())
	{
		if (MovementVector.X != 0.0f)
		{
			AddYawInput(MovementVector.X);
		}
		if (MovementVector.Y != 0.0f)
		{
			const FVector ForwardDirection = ControlledPawn->GetActorForwardVector();
			ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		}
	}
}
