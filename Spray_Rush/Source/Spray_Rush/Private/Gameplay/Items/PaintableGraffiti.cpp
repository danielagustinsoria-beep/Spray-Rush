// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Items/PaintableGraffiti.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Gameplay/Interfaces/PlayerInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Net/UnrealNetwork.h"
#include "Framework/Deathmatch/DeathmatchGameMode.h"
#include "Framework/Deathmatch/DeathmatchPlayerController.h"
#include "Framework/Deathmatch/DeathmatchPlayerState.h"

APaintableGraffiti::APaintableGraffiti()
{
    SetReplicates(true);
    PrimaryActorTick.bCanEverTick = true;

    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
    SetRootComponent(ItemMesh);

    BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
    BoxCollision->SetupAttachment(ItemMesh);
}

void APaintableGraffiti::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APaintableGraffiti, bIsPaintable);
    DOREPLIFETIME(APaintableGraffiti, PaintColor);
}

void APaintableGraffiti::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    // Solo el servidor decide. Los clientes reciben el resultado por replicacion.
    if (!HasAuthority() || !OtherActor || !bIsPaintable) return;
    if (!OtherActor->Implements<UPlayerInterface>()) return;

    // Solo se puede pintar con la partida en curso.
    ADeathmatchGameMode* GM = GetWorld()->GetAuthGameMode<ADeathmatchGameMode>();
    if (!GM || !GM->IsMatchInProgress()) return;

    APawn* Pawn = Cast<APawn>(OtherActor);
    if (!Pawn) return;

    ADeathmatchPlayerState* PS = Cast<ADeathmatchPlayerState>(Pawn->GetPlayerState());
    ADeathmatchPlayerController* PC = Cast<ADeathmatchPlayerController>(Pawn->GetController());
    if (!PS) return;

    const FName TargetSocketName = TEXT("Hand_RSocket");
    AActor* Spray = IPlayerInterface::Execute_GetAttachedActorInSocket(OtherActor, TargetSocketName);

    if (!Spray)
    {
        // Client RPC: el aviso le llega solo al jugador que lo necesita.
        if (PC) PC->Client_ShowMessage(TEXT("No tienes lata para pintar."));
        return;
    }

    Spray->Destroy();
    PS->SetHasCan(false);

    // Cambio de estado en el servidor: se replica a todos los clientes.
    PaintColor = PS->PlayerColor;
    bIsPaintable = false;
    OnRep_IsPaintable(); // El servidor/host no recibe el RepNotify solo: se llama a mano.

    PS->AddPaintedWall();

    Multicast_PlayPaintFX(GetActorLocation(), PaintColor);

    if (PC) PC->Client_ShowMessage(TEXT("¡Pintaste una pared!"));

    // Ultimo paso: el GameMode revisa si este jugador llego al objetivo.
    GM->WallPainted(PS);
}

void APaintableGraffiti::OnRep_IsPaintable()
{
    ApplyPaintVisual();
}

void APaintableGraffiti::ApplyPaintVisual()
{
    if (bIsPaintable || !ItemMesh) return;

    if (!PaintMID)
    {
        PaintMID = ItemMesh->CreateAndSetMaterialInstanceDynamic(0);
    }
    if (PaintMID)
    {
        PaintMID->SetVectorParameterValue(ColorParameterName, PaintColor);
    }
}

void APaintableGraffiti::Multicast_PlayPaintFX_Implementation(FVector Location, FLinearColor Color)
{
    BP_PlayPaintFX(Location, Color);
}

void APaintableGraffiti::BeginPlay()
{
    Super::BeginPlay();
}

void APaintableGraffiti::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}