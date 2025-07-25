// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"

class UAnimMontage;
class USoundBase;
class UActorAttributes;
class UHealthBarComponent;

UCLASS()
class CPPCOURSE_API AEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	AEnemy();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
protected:
	virtual void BeginPlay() override;
	/**
	* PlayingMontages
	*/
	void PlayHitReactMontage(FName SectionName);
	void PlayDeathMontage();

	UPROPERTY()
	AActor* CombatActor;

	//MONTAGES
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, Category = ViusalEffects)
	UParticleSystem* HitParticles;

	UPROPERTY(BlueprintReadOnly)
	EDeathPose DeathPose = EDeathPose::EDP_Alive;

private:
	UPROPERTY(VisibleAnywhere)
	UActorAttributes* Attributes;

	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(EditAnywhere)
	float CombatRadius = 500.f;

public:	
	virtual void GetHit_Implementation(const FVector& ImpactPoint);
	void DirectionalHitImapct(const FVector& ImpactPoint);

	UPROPERTY(EditDefaultsOnly, Category = "SoundEffects")
	USoundBase* HitFleshSound;
};
