// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Weapon.generated.h"

/**
 * 
 */
class USoundBase; 

UCLASS()
class CPPCOURSE_API AWeapon : public AItem
{
	GENERATED_BODY()
	
protected:
	virtual void OnSphereCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnEndSphereCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

public:
	void Equip(USceneComponent* InParent, FName InSocketName);
	void AttachMeshToSocket(USceneComponent* InParent, FName InSocketName);
private:
	UPROPERTY(EditAnywhere)
	USoundBase* EquipSound;
};
