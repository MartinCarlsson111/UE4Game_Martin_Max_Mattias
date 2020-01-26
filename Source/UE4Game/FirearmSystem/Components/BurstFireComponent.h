// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponTriggerComponent.h"
#include "BurstFireComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Trigger), Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UE4GAME_API UBurstFireComponent : public UWeaponTriggerComponent
{
	GENERATED_BODY()
	


public:
	void OnFire_Implementation(FWeaponMode WeaponMode) override;

	//The time between burst shots
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BurstFire)
	float BurstRate = 0.1f;

	//The amount of burst shots
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BurstFire)
	int BurstCount = 3;

	//the cooldown for activating the trigger
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BurstFire)
	float Cooldown = 0.5f;

	FTimerHandle CooldownHandle;
	FTimerHandle BurstFireHandle;

	UFUNCTION()
	void CooldownFinished();

	UFUNCTION()
	void BurstFire(FWeaponMode WeaponMode);

	bool Shoot(FWeaponMode WeaponMode);

private:
	int NumberOfBulletsFired = 0;
};
