#include "Item/Weapons/Weapon.h"
#include "Characters/MainRPGCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "CppCourse/DebugShapes.h"
#include "Components/SceneComponent.h"
#include "Interfaces/HitInterface.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

class AMainRPGCharacter;


AWeapon::AWeapon()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Collision"));
	BoxCollision->SetupAttachment(GetRootComponent());
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	TraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("TraceStart"));
	TraceStart->SetupAttachment(GetRootComponent());

	TraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("TraceEnd"));
	TraceEnd->SetupAttachment(GetRootComponent());
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxCollision);
}

void AWeapon::OnSphereCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereCollision(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::OnEndSphereCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndSphereCollision(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AWeapon::OnBoxCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector Start = TraceStart->GetComponentLocation();
	FVector End = TraceEnd->GetComponentLocation();
	FHitResult BoxHit;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	for (AActor* Actors : IgnoreActors)
	{
		ActorsToIgnore.AddUnique(Actors);
	}

	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start, 
		End,
		FVector(5.f,5.f,5.f),
		TraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false, 
		ActorsToIgnore, 
		EDrawDebugTrace::None, 
		BoxHit,
		true
		);

	if (BoxHit.GetActor())
	{
		IHitInterface* HitInterface = Cast<IHitInterface>(BoxHit.GetActor());

		if (HitInterface)
		{
			HitInterface->Execute_GetHit(BoxHit.GetActor(), BoxHit.ImpactPoint);
		}
		IgnoreActors.AddUnique(BoxHit.GetActor());

		CreateFields(BoxHit.ImpactPoint);
	}
}

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName)
{
	FAttachmentTransformRules TransformRule(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(InParent, TransformRule, InSocketName);
	ItemState = EItemState::EIS_Equipped;
	if (EquipSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			EquipSound,
			GetActorLocation()
		);
	}
	if (SphereCollision)
	{
		SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AWeapon::AttachMeshToSocket(USceneComponent* InParent, FName InSocketName)
{
	FAttachmentTransformRules TransformRule(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(InParent, TransformRule, InSocketName);
}



