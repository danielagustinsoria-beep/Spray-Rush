// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "DeathmatchWidget.generated.h"

class UImage;
class UTextBlock;
class UVerticalBox;
class UHorizontalBox;

/**
 * 
 */
UCLASS()
class SPRAY_RUSH_API UDeathmatchWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Score;
	
	//Player 1
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HorizontalBox_Player1;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Player1;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Player1;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_ScorePlayer1;
	
	//Player 2
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HorizontalBox_Player2;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Player2;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Player2;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_ScorePlayer2;
	
	//Player 3
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HorizontalBox_Player3;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Player3;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Player3;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_ScorePlayer3;
	
	//Player 4
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HorizontalBox_Player4;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Player4;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Player4;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_ScorePlayer4;
};
