// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Enemy.generated.h"

class UAnimMontage;
class USoundBase;

UCLASS()
class CPPCOURSE_API AEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	AEnemy();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	virtual void BeginPlay() override;
	/**
	* PlayingMontages
	*/
	void PlayHitReactMontage(FName SectionName);

	//MONTAGES
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere, Category = ViusalEffects)
	UParticleSystem* HitParticles;

public:	
	virtual void GetHit_Implementation(const FVector& ImpactPoint);
	void DirectionalHitImapct(const FVector& ImpactPoint);

	UPROPERTY(EditDefaultsOnly, Category = "SoundEffects")
	USoundBase* HitFleshSound;
};
