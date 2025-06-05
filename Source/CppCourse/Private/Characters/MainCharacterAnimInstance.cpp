// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/MainRPGCharacter.h"
#include "Kismet/KismetMathLibrary.h"

void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	MainCharacter = Cast<AMainRPGCharacter>(TryGetPawnOwner());
	if (MainCharacter)
	{
		CharacterMovement = MainCharacter->GetCharacterMovement();
	}
}

void UMainCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (CharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(CharacterMovement->Velocity);
		isFalling = CharacterMovement->IsFalling();
		CharacterState = MainCharacter->GetCurrentState();
	}
}
