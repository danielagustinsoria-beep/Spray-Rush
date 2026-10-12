// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"

#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	Button_SearchGame->OnClicked.AddDynamic(this, &UMainMenu::SwitchToSearchGame);
	Button_BackToMenu->OnClicked.AddDynamic(this, &UMainMenu::SwitchBackToMenu);
	Button_QuitGameMenu->OnClicked.AddDynamic(this, &UMainMenu::SwitchToQuitGameMenu);
	Button_QuitGameConfirmation->OnClicked.AddDynamic(this, &UMainMenu::QuitGameConfirmation);
	Button_DontQuit->OnClicked.AddDynamic(this, &UMainMenu::SwitchBackToMenu);
	Button_Options->OnClicked.AddDynamic(this, &UMainMenu::SwitchToOptionsMenu);
	Button_BackToMenu_Options->OnClicked.AddDynamic(this, &UMainMenu::SwitchBackToMenu);
	Button_BackToMenu_Options_1->OnClicked.AddDynamic(this, &UMainMenu::SwitchBackToMenu);
	Button_ToListenServer->OnClicked.AddDynamic(this, &UMainMenu::SwitchToListenServer);
	Button_Host->OnClicked.AddDynamic(this, &UMainMenu::OnButtonHostClicked);
	Button_JoinServer->OnClicked.AddDynamic(this, &UMainMenu::OnButtonJoinServerClicked);
	
	//Disable Tutorial Button
	//Tutorial_Button->SetIsEnabled(false);
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

void UMainMenu::SwitchToListenServer()
{
	MenuSwitcher->SetActiveWidgetIndex(5);
}

void UMainMenu::OnButtonHostClicked()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Level, true, TEXT("Listen"));
}

void UMainMenu::OnButtonJoinServerClicked()
{
	const FString IP = EditableTextBox_IPAdress->GetText().ToString();
	UGameplayStatics::OpenLevel(this, FName(*IP));
}

