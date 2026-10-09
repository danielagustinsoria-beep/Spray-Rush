// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaintableGraffiti.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class SPRAY_RUSH_API APaintableGraffiti : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APaintableGraffiti();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	UStaticMeshComponent* ItemMesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	UBoxComponent* BoxCollision;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	bool bIsPaintable = true;
};
