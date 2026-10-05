// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/WidgetSwitcher.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	SearchGame_Button->OnClicked.AddDynamic(this, &UMainMenu::SwitchToSearchGame);
	BackToMenu_Button->OnClicked.AddDynamic(this, &UMainMenu::SwitchBackToMenu);
	QuitGameMenu_Button->OnClicked.AddDynamic(this, &UMainMenu::SwitchToQuitGameMenu);
	QuitGameConfirmation_Button->OnClicked.AddDynamic(this, &UMainMenu::QuitGameConfirmation);
	DontQuit_Button->OnClicked.AddDynamic(this, &UMainMenu::SwitchBackToMenu);
	Options_Button->OnClicked.AddDynamic(this, &UMainMenu::SwitchToOptionsMenu);
	BackToMenu_Options->OnClicked.AddDynamic(this, &UMainMenu::SwitchBackToMenu);
	
	//Disable Tutorial Button
	Tutorial_Button->SetIsEnabled(false);
}

void UMainMenu::SwitchToSearchGame()
{
	MenuSwitcher->SetActiveWidgetIndex(1);	
}

void UMainMenu::SwitchBackToMenu()
{
	MenuSwitcher->SetActiveWidgetIndex(0);
}

void UMainMenu::SwitchToQuitGameMenu()
{
	MenuSwitcher->SetActiveWidgetIndex(2);
}

void UMainMenu::QuitGameConfirmation()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit,false);
}

void UMainMenu::SwitchToOptionsMenu()
{
	MenuSwitcher->SetActiveWidgetIndex(4);
}

