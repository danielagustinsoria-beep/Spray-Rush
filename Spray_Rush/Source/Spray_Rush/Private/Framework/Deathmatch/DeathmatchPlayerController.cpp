// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Deathmatch/DeathmatchPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "Characters/Character_J.h"
#include "Framework/Deathmatch/DeathmatchGameMode.h"
#include "Gameplay/Items/ItemEquipBase.h"
#include "UI/DeathmatchHUDWidget.h"

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

	// El HUD solo existe en la maquina del jugador dueno de este controller.
	if (IsLocalController() && HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UDeathmatchHUDWidget>(this, HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}

void ADeathmatchPlayerController::Client_ShowMessage_Implementation(const FString& Message)
{
	const TCHAR* Where = (GetNetMode() == NM_Client) ? TEXT("Cliente") : TEXT("Servidor");
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("[%s] %s"), Where, *Message));
	}
}

void ADeathmatchPlayerController::Server_TrySteal_Implementation()
{
	// Esto corre SOLO en el servidor: aca se valida todo.
	ADeathmatchGameMode* GM = GetWorld()->GetAuthGameMode<ADeathmatchGameMode>();
	APawn* MyPawn = GetPawn();
	if (!GM || !GM->IsMatchInProgress() || !MyPawn) return;

	// Busca la lata mas cercana que lleve OTRO jugador y este al alcance.
	AItemEquipBase* Target = nullptr;
	float BestDistSq = TNumericLimits<float>::Max();

	for (TActorIterator<AItemEquipBase> It(GetWorld()); It; ++It)
	{
		AItemEquipBase* Can = *It;
		AActor* Holder = Can->GetAttachParentActor();
		if (!Holder || Holder == MyPawn) continue;
		if (!Can->IsInStealRange(MyPawn)) continue;

		const float DistSq = FVector::DistSquared(MyPawn->GetActorLocation(), Can->GetActorLocation());
		if (DistSq < BestDistSq)
		{
			BestDistSq = DistSq;
			Target = Can;
		}
	}

	if (!Target)
	{
		Client_ShowMessage(TEXT("No hay ninguna lata al alcance."));
		return;
	}

	if (!Target->TryEquipTo(MyPawn))
	{
		Client_ShowMessage(TEXT("No pudiste robarla (¿ya llevas una o fue robada hace poco?)."));
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

		if (IA_Interact)
		{
			EnhancedInputComponent->BindAction(
				IA_Interact,
				ETriggerEvent::Started,
				this,
				&ADeathmatchPlayerController::HandleInteract
			);
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

void ADeathmatchPlayerController::HandleInteract(const FInputActionValue& Value)
{
	Server_TrySteal();
}