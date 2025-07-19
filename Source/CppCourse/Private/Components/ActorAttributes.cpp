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


void UActorAttributes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

