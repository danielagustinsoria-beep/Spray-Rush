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

    // Recoger una lata del suelo sigue siendo automatico (solo servidor).
    // Robarle la lata a otro jugador NO ocurre por overlap: requiere la tecla E
    // (ver ADeathmatchPlayerController::Server_TrySteal).
    if (!HasAuthority() || !OtherActor) return;
    if (GetAttachParentActor()) return;

    TryEquipTo(OtherActor);
}

bool AItemEquipBase::TryEquipTo(AActor* NewHolder)
{
    if (!HasAuthority() || !NewHolder) return false;
    if (!NewHolder->Implements<UPlayerInterface>()) return false;

    // Si la lata ya esta en manos de este jugador, no hay nada que hacer.
    AActor* PreviousHolder = GetAttachParentActor();
    if (PreviousHolder == NewHolder) return false;

    // Una lata recien robada no puede robarse de vuelta al instante.
    const float Now = GetWorld()->GetTimeSeconds();
    if (PreviousHolder && (Now - LastTransferTime) < StealCooldown) return false;

    // Un jugador solo puede llevar una lata a la vez.
    TArray<AActor*> Attached;
    NewHolder->GetAttachedActors(Attached);
    for (AActor* A : Attached)
    {
        if (A && A->IsA<AItemEquipBase>()) return false;
    }

    USkeletalMeshComponent* SkeletalMeshComponent = IPlayerInterface::Execute_GetSkeletalMesh(NewHolder);
    if (!SkeletalMeshComponent) return false;

    AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
    LastTransferTime = Now;

    if (ADeathmatchPlayerState* NewPS = GetDMPlayerState(NewHolder))
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

    return true;
}

bool AItemEquipBase::IsInStealRange(const AActor* Thief) const
{
    return Thief && FVector::Dist(Thief->GetActorLocation(), GetActorLocation()) <= StealRange;
}

void AItemEquipBase::BeginPlay()
{
    Super::BeginPlay();
}

void AItemEquipBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}