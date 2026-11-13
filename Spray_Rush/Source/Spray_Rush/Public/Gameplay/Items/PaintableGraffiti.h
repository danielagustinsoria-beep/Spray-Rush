// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaintableGraffiti.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UMaterialInstanceDynamic;

UCLASS()
class SPRAY_RUSH_API APaintableGraffiti : public AActor
{
    GENERATED_BODY()

public:
    APaintableGraffiti();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
    UStaticMeshComponent* ItemMesh;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
    UBoxComponent* BoxCollision;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // false = la pared ya fue pintada.
    // RepNotify: cuando cambia, los clientes ejecutan OnRep_IsPaintable y actualizan el color.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, ReplicatedUsing = OnRep_IsPaintable, Category = "Player")
    bool bIsPaintable = true;

    // Color del jugador que pintó la pared. Se replica junto con bIsPaintable.
    UPROPERTY(BlueprintReadOnly, Replicated, Category = "Player")
    FLinearColor PaintColor = FLinearColor::White;

    // Nombre del parametro Vector en el material de la pared.
    UPROPERTY(EditDefaultsOnly, Category = "Paint")
    FName ColorParameterName = TEXT("PaintColor");

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnRep_IsPaintable();

    // NetMulticast: el servidor lo llama y se ejecuta en todos (servidor y clientes).
    UFUNCTION(NetMulticast, Unreliable)
    void Multicast_PlayPaintFX(FVector Location, FLinearColor Color);

    // Implementalo en el Blueprint hijo: Niagara y sonido de pintura.
    UFUNCTION(BlueprintImplementableEvent, Category = "Paint")
    void BP_PlayPaintFX(FVector Location, FLinearColor Color);

public:
    virtual void Tick(float DeltaTime) override;

private:
    void ApplyPaintVisual();

    UPROPERTY(Transient)
    TObjectPtr<UMaterialInstanceDynamic> PaintMID;
};