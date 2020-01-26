// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponTriggerComponent.h"
#include "../WeaponMode.h"
#include "ChargeUpTriggerComponent.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerPull);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerRelease);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharged);
UCLASS(ClassGroup = (Trigger), meta = (BlueprintSpawnableComponent))
class UE4GAME_API UChargeUpTriggerComponent : public UWeaponTriggerComponent
{
	GENERATED_BODY()
public:
	void OnFire_Implementation(FWeaponMode WeaponMode);
	void OnStopFire_Implementation(FWeaponMode WeaponMode);

	UPROPERTY(BlueprintAssignable, Category = "Trigger", Meta = (ToolTip = "Event called when the component receives the command to fire"))
	FOnTriggerPull OnTriggerPull;
	UPROPERTY(BlueprintAssignable, Category = "Trigger", Meta = (ToolTip = "Event called when the shot is fully charged up"))
	FCharged OnFullyCharged;
	UPROPERTY(BlueprintAssignable, Category = "Trigger", Meta = (ToolTip = "Event called when the trigger is released"))
	FOnTriggerRelease OnTriggerRelease;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger", Meta = (ToolTip = "How long time after a shot has been fired it takes before it can shoot again"))
	float TimeBetweenShots = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger", Meta = (ToolTip = "How long it takes before the shot is fully charged and can be released"))
	float ChargeUpTime = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger", Meta = (ToolTip = "How long each step of charging takes"))
	float ChargeUpRate = 0.1f;

	void CooldownTimerFunction();
	void ChargeUpTimerFunction();
	float Timer = 0;
	float ChargeUpTimer = 0;
	virtual void BeginPlay() override;
	FTimerHandle CooldownTimer;
	FTimerHandle ChargeUpTimerHandle;
	bool bCanShoot = true;
};
