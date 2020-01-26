// Fill out your copyright notice in the Description page of Project Settings.

#include "ChargeUpTriggerComponent.h"
#include "../WeaponMode.h"
#include "AmmoComponent.h"
#include "WeaponBarrelComponent.h"
#include "BulletComponent.h"
void UChargeUpTriggerComponent::OnFire_Implementation(FWeaponMode WeaponMode)
{
	if (bCanShoot)
	{
		OnTriggerPull.Broadcast();
		if (FireState)
		{
			FireState = false;
			GetOwner()->GetWorldTimerManager().SetTimer(ChargeUpTimerHandle, this, &UChargeUpTriggerComponent::ChargeUpTimerFunction, ChargeUpRate, true);
		}
	}
}
void UChargeUpTriggerComponent::OnStopFire_Implementation(FWeaponMode WeaponMode)
{
	if (bCanShoot)
	{
		OnTriggerRelease.Broadcast();
		if (WeaponMode.AmmoComponent->IsAmmoAvailable() && ChargeUpTimer >= ChargeUpTime)
		{
			WeaponMode.AmmoComponent->UseAmmo();
			WeaponMode.BarrelComponent->OnFire(WeaponMode.BulletComponent);
			GetOwner()->GetWorldTimerManager().SetTimer(CooldownTimer, this, &UChargeUpTriggerComponent::CooldownTimerFunction, ChargeUpRate, true);
			bCanShoot = false;
		}
		FireState = true;
		ChargeUpTimer = 0;
	}
}

void UChargeUpTriggerComponent::CooldownTimerFunction()
{
	Timer += 0.1f;
	if (Timer > TimeBetweenShots)
	{
		GetOwner()->GetWorldTimerManager().ClearTimer(CooldownTimer);
		bCanShoot = true;
		Timer = 0;
	}
}

void UChargeUpTriggerComponent::ChargeUpTimerFunction()
{
	if (ChargeUpTimer < ChargeUpTime)
	{
		ChargeUpTimer += 0.1f;
	}
	else
	{
		GetOwner()->GetWorldTimerManager().ClearTimer(ChargeUpTimerHandle);
	}
}

void UChargeUpTriggerComponent::BeginPlay()
{
}
