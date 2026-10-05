// Fill out your copyright notice in the Description page of Project Settings.


#include "Spray_Rush/Public/Framework/MenuPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/Application/SlateApplication.h"
#include "Spray_Rush/Public/UI/MainMenu.h"

AMenuPlayerController::AMenuPlayerController()
{}

void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (WidgetMainMenuReference)
	{
		
		WidgetMainMenu = CreateWidget<UMainMenu>(this, WidgetMainMenuReference);
        
		if (WidgetMainMenu)
		{
			WidgetMainMenu->AddToViewport();
			WidgetMainMenu->SearchGame_Button->OnClicked.AddDynamic(this, &AMenuPlayerController::SwitchToSearchMatchCamera);
			WidgetMainMenu->BackToMenu_Button->OnClicked.AddDynamic(this, &AMenuPlayerController::SwitchToMainMenuCamera);
			WidgetMainMenu->Options_Button->OnClicked.AddDynamic(this, &AMenuPlayerController::SwitchToOptionsCamera);
			WidgetMainMenu->BackToMenu_Options->OnClicked.AddDynamic(this, &AMenuPlayerController::SwitchToMainMenuCamera);
		}
	}
	
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	FInputModeUIOnly InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeData);
	
	// Buscar actores por Tag en el nivel
	TArray<AActor*> FoundActors;
    
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Cam_Main"), FoundActors);
	if (FoundActors.Num() > 0)
	{
		MainMenuCamera = FoundActors[0];
		// Establecer la cámara inicial inmediatamente sin blend
		SetViewTarget(MainMenuCamera);
		
	}

	FoundActors.Empty();
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Cam_SearchMatch"), FoundActors);
	if (FoundActors.Num() > 0)
	{
		SearchMatchCamera = FoundActors[0];
	}
	
	FoundActors.Empty();
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Cam_Options"), FoundActors);
	if (FoundActors.Num() > 0)
	{
		OptionsCamera = FoundActors[0];
	}
}

void AMenuPlayerController::SwitchToMainMenuCamera()
{
	float BlendTime = 0.5f;
	if (MainMenuCamera)
	{
		SetViewTargetWithBlend(MainMenuCamera, BlendTime, EViewTargetBlendFunction::VTBlend_EaseInOut, 2.0f, true);
	}
}

void AMenuPlayerController::SwitchToSearchMatchCamera()
{
	float BlendTime = 0.5f;
	if (SearchMatchCamera)
	{
		SetViewTargetWithBlend(SearchMatchCamera, BlendTime, EViewTargetBlendFunction::VTBlend_EaseInOut, 2.0f, true);
	}
}

void AMenuPlayerController::SwitchToOptionsCamera()
{
	float BlendTime = 0.5f;
	if (OptionsCamera)
	{
		SetViewTargetWithBlend(OptionsCamera, BlendTime, EViewTargetBlendFunction::VTBlend_EaseInOut, 2.0f, true);
	}
}

