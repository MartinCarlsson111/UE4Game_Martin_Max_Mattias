// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponAnimationComponent.h"
#include "../WeaponBase.h"
#include "../../UE4GameCharacter.h"
#include "WeaponBarrelComponent.h"

// Sets default values for this component's properties
UWeaponAnimationComponent::UWeaponAnimationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	// ...
}

// Called when the game starts
void UWeaponAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<AWeaponBase>(GetOwner());
	if (Owner)
	{
		Owner->PickedUp.AddDynamic(this, &UWeaponAnimationComponent::PlayPickUpAnimation);
		Owner->FindComponentByClass<UWeaponBarrelComponent>()->OnShoot.AddDynamic(this, &UWeaponAnimationComponent::PlayFireAnimation);
	}
	// ...
}

void UWeaponAnimationComponent::PlayFireAnimation()
{
	if (Owner && Owner->OwningPlayer)
	{
		Owner->OwningPlayer->PlayAnimation(FireAnimation);
	}
}

void UWeaponAnimationComponent::PlayReloadAnimation()
{
	if (Owner && Owner->OwningPlayer)
	{
		Owner->OwningPlayer->PlayAnimation(ReloadAnimation);
	}
}

void UWeaponAnimationComponent::PlayPickUpAnimation()
{
	if (Owner && Owner->OwningPlayer)
	{
		Owner->OwningPlayer->PlayAnimation(PickUpAnimation);
		if (!bHasBoundReload)
		{
			bHasBoundReload = true;
			Owner->OwningPlayer->OnReload.AddDynamic(this, &UWeaponAnimationComponent::PlayReloadAnimation);
		}
	}
}
