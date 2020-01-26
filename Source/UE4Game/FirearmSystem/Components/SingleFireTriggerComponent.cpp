// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleFireTriggerComponent.h"
#include "AmmoComponent.h"
#include "WeaponBarrelComponent.h"
#include "BulletComponent.h"
void USingleFireTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	TimerDel.BindUObject(this, &USingleFireTriggerComponent::OnCooldownFinished);
}


void USingleFireTriggerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(CooldownTimer);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void USingleFireTriggerComponent::OnFire_Implementation(FWeaponMode WeaponMode)
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(CooldownTimer))
	{
		if (!FireState)
		{
			if (WeaponMode.AmmoComponent->IsAmmoAvailable())
			{
				WeaponMode.AmmoComponent->UseAmmo();
				WeaponMode.BarrelComponent->OnFire(WeaponMode.BulletComponent);
			}
			FireState = true;
			GetWorld()->GetTimerManager().SetTimer(CooldownTimer, TimerDel , Cooldown, false);
		}
	}
}

void USingleFireTriggerComponent::OnStopFire_Implementation(FWeaponMode WeaponMode)
{
	if (FireState)
	{
		FireState = false;
	}
}

void USingleFireTriggerComponent::OnCooldownFinished()
{
	GetWorld()->GetTimerManager().ClearTimer(CooldownTimer);
}

