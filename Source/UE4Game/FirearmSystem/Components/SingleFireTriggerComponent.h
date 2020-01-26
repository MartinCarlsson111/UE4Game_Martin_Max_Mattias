// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponTriggerComponent.h"
#include "TimerManager.h"
#include "Engine/EngineTypes.h"
#include "SingleFireTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Trigger), meta = (BlueprintSpawnableComponent), BlueprintType, Blueprintable)
class UE4GAME_API USingleFireTriggerComponent : public UWeaponTriggerComponent
{
	GENERATED_BODY()

public:

	FTimerHandle CooldownTimer;
	FTimerDelegate TimerDel;

	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//Cooldown between shots
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trigger)
	float Cooldown = 0.5f;

	UFUNCTION()
	void OnCooldownFinished();

	void OnFire_Implementation(FWeaponMode WeaponMode) override;
	void OnStopFire_Implementation(FWeaponMode WeaponMode) override;

};
