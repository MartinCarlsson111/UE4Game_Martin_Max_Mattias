#pragma once

#include "CoreMinimal.h"
#include "WeaponMode.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FWeaponMode
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	class UWeaponTriggerComponent* TriggerComponent;
	UPROPERTY(BlueprintReadWrite)
	class UAmmoComponent* AmmoComponent;
	UPROPERTY(BlueprintReadWrite)
	class UWeaponBarrelComponent* BarrelComponent;
	UPROPERTY(BlueprintReadWrite)
	class UBulletComponent* BulletComponent;

	void Setup(
		class UWeaponTriggerComponent* NewTriggerComponent,
		class UAmmoComponent* NewAmmoComponent,
		class UWeaponBarrelComponent* NewBarrelComponent,
		class UBulletComponent* NewBulletComponent);

	void OnFire();
	void OnStopFire();
};