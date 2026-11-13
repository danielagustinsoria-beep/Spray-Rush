// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemEquipBase.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class SPRAY_RUSH_API AItemEquipBase : public AActor
{
	GENERATED_BODY()

public:
	AItemEquipBase();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FName SocketName = "";

	// Segundos durante los que una lata robada no puede volver a robarse.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	float StealCooldown = 1.5f;

	float LastTransferTime = -100.f;
};