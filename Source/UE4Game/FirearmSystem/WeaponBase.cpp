// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponBase.h"
#include "../UE4GameCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WeaponBarrelComponent.h"
#include "Components/WeaponTriggerComponent.h"
#include "Components/AmmoComponent.h"
AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Gun Mesh"));
	FireSound = CreateDefaultSubobject<USoundBase>("Fire Sound");
}

void AWeaponBase::AddWeaponMode(UAmmoComponent *WeaponAmmoComponent, UWeaponTriggerComponent *WeaponTriggerComponent, UWeaponBarrelComponent *WeaponBarrelComponent, UBulletComponent *WeaponBulletComponent)
{
	if (!WeaponAmmoComponent || !WeaponTriggerComponent || !WeaponBarrelComponent || !WeaponBulletComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("AddWeaponMode called with null components."))
		return;
	}
	FWeaponMode WeaponMode;

	WeaponMode.Setup(WeaponTriggerComponent, WeaponAmmoComponent, WeaponBarrelComponent, WeaponBulletComponent);
	WeaponModes.Add(WeaponMode);
}

void AWeaponBase::Interact_Implementation(ACharacter *PickupActor)
{
	OwningPlayer = Cast<AUE4GameCharacter>(PickupActor);
	if (OwningPlayer)
	{
		GunMesh->SetSimulatePhysics(false);
		OwningPlayer->EquipWeapon(this);
		GunMesh->SetCollisionProfileName(TEXT("NoCollision"));
		PlaySound(PickupSound);
		PickedUp.Broadcast();
	}
}

void AWeaponBase::OnReload()
{
	if (WeaponModes.Num() > CurrentWeaponModeIndex)
	{
		WeaponModes[CurrentWeaponModeIndex].AmmoComponent->Reload();
	}
}

void AWeaponBase::OnFire()
{
	Firing();
	FiringWeapon.Broadcast();
	if (WeaponModes.Num() > 0)
	{
		WeaponModes[CurrentWeaponModeIndex].OnFire();
	}
}

void AWeaponBase::CycleWeaponModes()
{
	CurrentWeaponModeIndex++;
	if (CurrentWeaponModeIndex >= WeaponModes.Num())
	{
		CurrentWeaponModeIndex = 0;
	}
}

void AWeaponBase::PlaySound(USoundBase *Sound)
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
	}
}
void AWeaponBase::OnStopFire()
{
	if (WeaponModes.Num() > 0)
	{
		WeaponModes[CurrentWeaponModeIndex].OnStopFire();
	}
}