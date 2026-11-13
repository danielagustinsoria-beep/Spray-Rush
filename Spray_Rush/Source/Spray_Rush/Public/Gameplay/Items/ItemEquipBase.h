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

	// Solo servidor. Equipa esta lata a NewHolder (recoger del suelo o robar).
	// Devuelve true si lo logra.
	bool TryEquipTo(AActor* NewHolder);

	// true si Thief esta a menos de StealRange de esta lata.
	bool IsInStealRange(const AActor* Thief) const;

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

	// Distancia maxima (en unidades) a la que se puede robar esta lata con la tecla E.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	float StealRange = 150.f;

	float LastTransferTime = -100.f;
};