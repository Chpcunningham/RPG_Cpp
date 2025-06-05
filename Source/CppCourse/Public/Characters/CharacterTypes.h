#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unequiped UMETA(DisplayName = "Unequiped"),
	ECS_OneHandedEquip UMETA(DisplayName = "OneHandedEquip"),
	ECS_TwoHandedEquip UMETA(DisplayName = "TwoHandedEquip")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	EAS_EquippingWeapon UMETA(DisplayName = "Equipping Weapon")
};
