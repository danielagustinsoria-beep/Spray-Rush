#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraActor.h"
#include "UI/MainMenu.h"
#include "MenuPlayerController.generated.h"

class ACameraActor;

UCLASS()
class SPRAY_RUSH_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UMainMenu> WidgetMainMenu;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WidgetMainMenuReference;
	
	UPROPERTY()
	TObjectPtr<AActor> MainMenuCamera;

	UPROPERTY()
	TObjectPtr<AActor> SearchMatchCamera;
	
	UPROPERTY()
	TObjectPtr<AActor> OptionsCamera;
	
public:
	AMenuPlayerController();
	
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SwitchToMainMenuCamera(float BlendTime = 0.5f);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SwitchToSearchMatchCamera(float BlendTime = 0.5f);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SwitchToOptionsCamera(float BlendTime = 0.5f);
};