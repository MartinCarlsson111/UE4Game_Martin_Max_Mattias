#include "AmmoComponent.h"
#include "DrawDebugHelpers.h"
#include "../WeaponBase.h"
#include "Kismet/GameplayStatics.h"
bool UAmmoComponent::IsAmmoAvailable_Implementation()
{
	if ((CurrentAmmoCount-CurrentMagazine.NAmmoPerUse) > 0)
	{
		return true;
	}
	OnOutOfAmmo();
	return false;
}

void UAmmoComponent::UseAmmo_Implementation()
{
	CurrentAmmoCount -= CurrentMagazine.NAmmoPerUse;
}

int UAmmoComponent::GetCurrentAmmoCount()
{
	return CurrentAmmoCount;
}

void UAmmoComponent::Reload_Implementation(int AmountToReload)
{
	if (Magazines.Num() > 0)
	{
		CurrentAmmoCount = Magazines[0].MagazineSize;
		CurrentMagazine = Magazines[0];
		Magazines.Pop(true);
		AWeaponBase* Owner = Cast<AWeaponBase>(GetOwner());
		if (Owner && Owner->ReloadSound)
		{
			Owner->PlaySound(Owner->ReloadSound);
		}
	}
}

void UAmmoComponent::OnOutOfAmmo_Implementation()
{
}
