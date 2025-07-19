// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Treasure.h"
#include "Characters/MainRPGCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Item/Treasure.h"
void ATreasure::OnSphereCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMainRPGCharacter* MainCharacter = Cast<AMainRPGCharacter>(OtherActor))
	{
		if (PickupSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				PickupSound,
				GetActorLocation()
			);
			Destroy();
		}
	}
}
