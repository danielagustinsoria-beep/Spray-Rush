// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Items/ItemEquipBase.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "Gameplay/Interfaces/PlayerInterface.h"
#include "Framework/Deathmatch/DeathmatchPlayerController.h"
#include "Framework/Deathmatch/DeathmatchPlayerState.h"

namespace
{
    ADeathmatchPlayerState* GetDMPlayerState(AActor* Holder)
    {
        const APawn* Pawn = Cast<APawn>(Holder);
        return Pawn ? Cast<ADeathmatchPlayerState>(Pawn->GetPlayerState()) : nullptr;
    }
}

AItemEquipBase::AItemEquipBase()
{
    SetReplicates(true);
    PrimaryActorTick.bCanEverTick = true;

    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
    SetRootComponent(ItemMesh);

    SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
    SphereCollision->SetupAttachment(ItemMesh);
    SphereCollision->SetSphereRadius(100.0f);
}

void AItemEquipBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    // Recoger y robar lo decide solo el servidor.
    if (!HasAuthority() || !OtherActor) return;
    if (!OtherActor->Implements<UPlayerInterface>()) return;

    // Si la lata ya esta en manos de este jugador, no hay nada que hacer.
    AActor* PreviousHolder = GetAttachParentActor();
    if (PreviousHolder == OtherActor) return;

    // Una lata recien robada no puede robarse de vuelta al instante.
    const float Now = GetWorld()->GetTimeSeconds();
    if (PreviousHolder && (Now - LastTransferTime) < StealCooldown) return;

    // Un jugador solo puede llevar una lata a la vez.
    TArray<AActor*> Attached;
    OtherActor->GetAttachedActors(Attached);
    for (AActor* A : Attached)
    {
        if (A && A->IsA<AItemEquipBase>()) return;
    }

    USkeletalMeshComponent* SkeletalMeshComponent = IPlayerInterface::Execute_GetSkeletalMesh(OtherActor);
    if (!SkeletalMeshComponent) return;

    AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
    LastTransferTime = Now;

    if (ADeathmatchPlayerState* NewPS = GetDMPlayerState(OtherActor))
    {
        NewPS->SetHasCan(true);
    }

    // Si se la quitaron a alguien, esa persona deja de llevarla y recibe un aviso.
    if (PreviousHolder)
    {
        if (ADeathmatchPlayerState* OldPS = GetDMPlayerState(PreviousHolder))
        {
            OldPS->SetHasCan(false);
        }
        const APawn* OldPawn = Cast<APawn>(PreviousHolder);
        if (ADeathmatchPlayerController* PC = OldPawn ? Cast<ADeathmatchPlayerController>(OldPawn->GetController()) : nullptr)
        {
            PC->Client_ShowMessage(TEXT("¡Te robaron la lata!"));
        }
    }
}

void AItemEquipBase::BeginPlay()
{
    Super::BeginPlay();
}

void AItemEquipBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}