// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainRPGCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GroomComponent.h"
#include "Animation/AnimInstance.h" 
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Item/Item.h"
#include "Item/Weapons/Weapon.h"

AMainRPGCharacter::AMainRPGCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	PlayerSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	PlayerSpringArm->SetupAttachment(GetRootComponent());
	PlayerSpringArm->TargetArmLength = 300.f;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(PlayerSpringArm);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");
}

//Following functions are for movement
void AMainRPGCharacter::Movement(const FInputActionValue& Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	if (Controller)
	{
		const FVector2D MovementValue = Value.Get<FVector2D>();

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardVector, MovementValue.Y);
		AddMovementInput(RightVector, MovementValue.X);
	}
}
void AMainRPGCharacter::Jump()
{
	if (ActionState == EActionState::EAS_Unoccupied)
	{
		return ACharacter::Jump();
	}
	else {
		return;
	}
}
void AMainRPGCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (GetController())
	{
		AddControllerPitchInput(LookAxisValue.Y);
		AddControllerYawInput(LookAxisValue.X);
	}
}

//Following functions are for attacking
void AMainRPGCharacter::Attack(const FInputActionValue& Value)
{
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}

}
void AMainRPGCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}
bool AMainRPGCharacter::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequiped;
} 

//Functions for arming and disarming weapons
void AMainRPGCharacter::Disarm()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("WeaponSocket"));
	}
}
void AMainRPGCharacter::Arm()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("RighthandSocket"));
	}
}

void AMainRPGCharacter::FinishedEquipping()
{
	ActionState = EActionState::EAS_Unoccupied;
}
bool AMainRPGCharacter::CanDisarm()
{
	return ActionState == EActionState::EAS_Unoccupied && 
		CharacterState != ECharacterState::ECS_Unequiped;
}
bool AMainRPGCharacter::CanArm()
{
	return ActionState == EActionState::EAS_Unoccupied && 
		CharacterState == ECharacterState::ECS_Unequiped && 
		EquippedWeapon;
}

//E-key for equipping weapon
void AMainRPGCharacter::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		OverlappingWeapon->Equip(GetMesh(), FName("RighthandSocket"));
		CharacterState = ECharacterState::ECS_OneHandedEquip;
		OverlappingItem = nullptr;
		EquippedWeapon = OverlappingWeapon;

	}
	else
	{
		if (CanDisarm())
		{
			PlayEquipMontage(FName("Disarm"));
			CharacterState = ECharacterState::ECS_Unequiped;
			ActionState = EActionState::EAS_EquippingWeapon;
		}
		else if (CanArm())
		{
			PlayEquipMontage(FName("Equip"));
			CharacterState = ECharacterState::ECS_OneHandedEquip;
			ActionState = EActionState::EAS_EquippingWeapon;
		}
	}
}

//Montages
void AMainRPGCharacter::PlayAttackMontage()
{
	UAnimInstance* CharacterAnimInstance = GetMesh()->GetAnimInstance();
	if (CharacterAnimInstance && AttackMontage)
	{
		CharacterAnimInstance->Montage_Play(AttackMontage);
		const int32 Selection = FMath::RandRange(0, 3);
		FName SelectionName = FName();
		switch (Selection)
		{
		case 0:
			SelectionName = FName("Attack1");
			break;
		case 1:
			SelectionName = FName("Attack2");
			break;
		case 2:
			SelectionName = FName("Attack3");
			break;
		case 3:
			SelectionName = FName("Attack4");
			break;
		default:
			break;
		}
		CharacterAnimInstance->Montage_JumpToSection(SelectionName, AttackMontage);
	}
}
void AMainRPGCharacter::PlayEquipMontage(FName SectionName)
{
	UAnimInstance* CharacterAnimInstance = GetMesh()->GetAnimInstance();
	if (CharacterAnimInstance && EquipMontage)
	{
		
		CharacterAnimInstance->Montage_Play(EquipMontage);
		CharacterAnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
}

//BEGINPLAY
void AMainRPGCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* PlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			PlayerSubsystem->AddMappingContext(CharacterContext, 0);
		}
	}

}

//TICK
void AMainRPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//PLAYERINPUT
void AMainRPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMainRPGCharacter::Movement);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainRPGCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainRPGCharacter::Jump);
		EnhancedInputComponent->BindAction(PickupAction, ETriggerEvent::Triggered, this, &AMainRPGCharacter::EKeyPressed);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AMainRPGCharacter::Attack);
	}
}

