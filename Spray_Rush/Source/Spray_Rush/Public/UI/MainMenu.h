// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenu.generated.h"

class UWidgetSwitcher;

UCLASS()
class SPRAY_RUSH_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UWidgetSwitcher> MenuSwitcher;

public:
	
	// Propiedades
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SearchGame_Button;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Options_Button;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitGameMenu_Button;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitGameConfirmation_Button;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> DontQuit_Button;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackToMenu_Button;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackToMenu_Options;
	
	// Disabled
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Tutorial_Button;
	
	// Métodos
	
	UFUNCTION()
	void SwitchBackToMenu();
	
	UFUNCTION()
	void SwitchToQuitGameMenu();
	
	UFUNCTION()
	void QuitGameConfirmation();
	
	UFUNCTION()
	void SwitchToSearchGame();
	
	UFUNCTION()
	void SwitchToOptionsMenu();
};
