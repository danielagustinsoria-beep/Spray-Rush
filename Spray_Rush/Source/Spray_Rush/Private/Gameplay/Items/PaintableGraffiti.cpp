// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Items/PaintableGraffiti.h"

#include "Components/BoxComponent.h"
#include "Gameplay/Interfaces/PlayerInterface.h"


// Sets default values
APaintableGraffiti::APaintableGraffiti()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
	SetRootComponent(ItemMesh);
	ItemMesh->SetIsReplicated(true);
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxCollision->SetupAttachment(ItemMesh);
	
}

void APaintableGraffiti::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (!OtherActor) return;
	if (!HasAuthority()) return;
	if (OtherActor->Implements<UPlayerInterface>())
	{
		bIsPaintable = false;
	}
}

// Called when the game starts or when spawned
void APaintableGraffiti::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APaintableGraffiti::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

