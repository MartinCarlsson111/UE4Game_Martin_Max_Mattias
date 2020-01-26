// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponTriggerComponent.h"
#include "WeaponBarrelComponent.h"
#include "BulletComponent.h"
#include "AmmoComponent.h"
UWeaponTriggerComponent::UWeaponTriggerComponent()
{

}

void UWeaponTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponTriggerComponent::OnFire_Implementation(FWeaponMode WeaponMode)
{
	if (!FireState)
	{
		if (WeaponMode.AmmoComponent->IsAmmoAvailable())
		{
			WeaponMode.AmmoComponent->UseAmmo();
			WeaponMode.BarrelComponent->OnFire(WeaponMode.BulletComponent);
		}
		FireState = true;
	}
}

void UWeaponTriggerComponent::OnStopFire_Implementation(FWeaponMode WeaponMode)
{
	if (FireState)
	{
		FireState = false;
	}
}
