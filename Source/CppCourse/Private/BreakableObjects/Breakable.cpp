// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableObjects/Breakable.h"
#include "Characters/MainRPGCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Item/Treasure.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

// Sets default values
ABreakable::ABreakable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GeometryComponent = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryComponent"));
	SetRootComponent(GeometryComponent);
	GeometryComponent->SetGenerateOverlapEvents(true);
	GeometryComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GeometryComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

// Called when the game starts or when spawned
void ABreakable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakable::GetHit_Implementation(const FVector& ImpactPoint)
{
	if (bBroken) return;

	bBroken = true;
	UWorld* World = GetWorld();

	if (World)
	{
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Z += 75.f;

		int32 Selection = FMath::RandRange(0, TreasureClasses.Num() - 1);
		World->SpawnActor<ATreasure>(TreasureClasses[Selection], SpawnLocation, GetActorRotation());
	}
	
}


