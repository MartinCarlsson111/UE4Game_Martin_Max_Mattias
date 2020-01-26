// Fill out your copyright notice in the Description page of Project Settings.


#include "BurstFireComponent.h"
#include "AmmoComponent.h"
#include "WeaponBarrelComponent.h"
#include "BulletComponent.h"
void UBurstFireComponent::OnFire_Implementation(FWeaponMode WeaponMode)
{
	if (!FireState && !GetWorld()->GetTimerManager().TimerExists(BurstFireHandle) && !GetWorld()->GetTimerManager().TimerExists(CooldownHandle))
	{
		if (Shoot(WeaponMode))
		{
			NumberOfBulletsFired++;
			FTimerDelegate BurstFireDelegate = FTimerDelegate::CreateUObject(this, &UBurstFireComponent::BurstFire, WeaponMode);
			GetWorld()->GetTimerManager().SetTimer(CooldownHandle, this, &UBurstFireComponent::CooldownFinished, (BurstRate * BurstCount) + Cooldown, false);
			GetWorld()->GetTimerManager().SetTimer(BurstFireHandle, BurstFireDelegate, BurstRate, true);
			FireState = true;
		}
	}
}

void UBurstFireComponent::CooldownFinished()
{
	GetWorld()->GetTimerManager().ClearTimer(CooldownHandle);
}

void UBurstFireComponent::BurstFire(FWeaponMode WeaponMode)
{
	if ( NumberOfBulletsFired < BurstCount)
	{
		if (Shoot(WeaponMode)) {
			NumberOfBulletsFired++;
			return;
		}
	}
	NumberOfBulletsFired = 0;
	GetWorld()->GetTimerManager().ClearTimer(BurstFireHandle);
	FireState = false;
}

bool UBurstFireComponent::Shoot(FWeaponMode WeaponMode)
{
	if (WeaponMode.AmmoComponent->IsAmmoAvailable())
	{
		WeaponMode.AmmoComponent->UseAmmo();
		WeaponMode.BarrelComponent->OnFire(WeaponMode.BulletComponent);
		return true;
	}
	return false;
}