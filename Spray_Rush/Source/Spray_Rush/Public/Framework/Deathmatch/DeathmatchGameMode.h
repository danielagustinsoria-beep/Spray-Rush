// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DeathmatchGameMode.generated.h"

class APaintableGraffiti;
/**
 * 
 */
UCLASS()
class SPRAY_RUSH_API ADeathmatchGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ADeathmatchGameMode();
	
	virtual void StartMatch() override;
	
	virtual void BeginPlay() override;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	//void WallPainted();
	
	//void CheckWinCondition();
	
	//void DeclareWinner();
	
	FTimerHandle MatchStartTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Gamemode")
	float MatchStartTimeDuration;
	

	UPROPERTY(BlueprintReadOnly, Category = "Gamemode")
	TArray<TObjectPtr<APaintableGraffiti>> PaintableGraffitis;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gamemode");
	int32 ObjectivePaints = 5;
};
