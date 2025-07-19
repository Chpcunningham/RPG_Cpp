// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h" 

#include "CppCourse/DebugShapes.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "Characters/MainRPGCharacter.h"

FColor drawColor = FColor::Cyan;


// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.S
	PrimaryActorTick.bCanEverTick = true;
	//hellowork
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereCollision->SetupAttachment(GetRootComponent());

	EmbersEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Ember Effects"));
	EmbersEffect->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereCollision);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AItem::OnEndSphereCollision);
}

float AItem::TransformedSin()
{
	return Amplitude* FMath::Sin(RunningTime * TimeConstant);
}

void AItem::OnSphereCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMainRPGCharacter* MainCharacter = Cast<AMainRPGCharacter>(OtherActor))
	{
		MainCharacter->SetOverlappingItem(this);
	}
}

void AItem::OnEndSphereCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AMainRPGCharacter* MainCharacter = Cast<AMainRPGCharacter>(OtherActor))
	{
		MainCharacter->SetOverlappingItem(nullptr);
	}
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;

	if (ItemState == EItemState::EIS_Hovering)
	{
		AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));
	}
	
}
 
