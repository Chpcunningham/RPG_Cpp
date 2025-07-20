// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActorAttributes.h"

UActorAttributes::UActorAttributes()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UActorAttributes::BeginPlay()
{
	Super::BeginPlay();
}

void UActorAttributes::ReceiveDamage(float Damage)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);
}

float UActorAttributes::GetHealthPercent()
{
	return CurrentHealth / MaxHealth;
}

bool UActorAttributes::IsAlive()
{
	return CurrentHealth > 0.f;
}


void UActorAttributes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

