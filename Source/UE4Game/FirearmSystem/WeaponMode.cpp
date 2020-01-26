#include "WeaponMode.h"
#include "Components/WeaponTriggerComponent.h"
#include "Components/AmmoComponent.h"
#include "Components/WeaponBarrelComponent.h"
#include "Components/BulletComponent.h"
void FWeaponMode::Setup(UWeaponTriggerComponent* NewTriggerComponent, UAmmoComponent* NewAmmoComponent, UWeaponBarrelComponent* NewBarrelComponent, UBulletComponent* NewBulletComponent)
{
	AmmoComponent = NewAmmoComponent;
	TriggerComponent = NewTriggerComponent;
	BarrelComponent = NewBarrelComponent;
	BulletComponent = NewBulletComponent;
}

void FWeaponMode::OnFire()
{
	FWeaponMode* WeaponMode = this;

	TriggerComponent->OnFire(*WeaponMode);
}

void FWeaponMode::OnStopFire()
{
	TriggerComponent->OnStopFire(*this);
}
