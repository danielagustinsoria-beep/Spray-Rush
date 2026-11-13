// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "DeathmatchPlayerController.generated.h"

class UInputMappingContext;
class UDeathmatchHUDWidget;

UCLASS()
class SPRAY_RUSH_API ADeathmatchPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Client RPC: lo llama el servidor y se ejecuta solo en el cliente dueno de este controller.
	UFUNCTION(Client, Reliable)
	void Client_ShowMessage(const FString& Message);

protected:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	int32 MappingPriority = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	float velocityScale = 1.f;

	// Widget del HUD (WBP_HUD). Se elige en el Blueprint del controller.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UDeathmatchHUDWidget> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UDeathmatchHUDWidget> HUDWidget;
	
	void HandleJump(const FInputActionValue& Value);
	void HandleMove(const FInputActionValue& Value);
};