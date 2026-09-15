// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	BackToMenu->OnClicked.AddDynamic(this, &UMainMenu::SwitchToMenu);
}

void UMainMenu::SwitchToMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("The C++ button was clicked!"));
}
