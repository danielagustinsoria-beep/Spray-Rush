// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenu.generated.h"

class UWidgetSwitcher;
class UEditableTextBox;

UCLASS()
class SPRAY_RUSH_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UWidgetSwitcher> MenuSwitcher;

public:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_SearchGame;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Options;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_QuitGameMenu;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_QuitGameConfirmation;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_DontQuit;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_BackToMenu;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_BackToMenu_Options;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_ToListenServer;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_BackToMenu_Options_1;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Host;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_JoinServer;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> EditableTextBox_IPAdress;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Level;
	
	
	// Disabled
	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<UButton> Tutorial_Button;
	
	
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
	
	UFUNCTION()
	void SwitchToListenServer();
	
	UFUNCTION()
	void OnButtonHostClicked();
	
	UFUNCTION()
	void OnButtonJoinServerClicked();
};
