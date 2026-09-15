// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class SPRAY_RUSH_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void SwitchToMenu();

public:
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UButton> Tutorial;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UButton> SearchGame;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UButton> QuitGame;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UButton> Options;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UButton> ExitGame;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UButton> DontQuit;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackToMenu;
};
