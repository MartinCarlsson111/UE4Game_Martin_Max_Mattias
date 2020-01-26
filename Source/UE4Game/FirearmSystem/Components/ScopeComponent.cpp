// Fill out your copyright notice in the Description page of Project Settings.

#include "ScopeComponent.h"
#include "../WeaponBase.h"
#include "WeaponBarrelComponent.h"
#include "Camera/CameraComponent.h"
#include "../../UE4GameCharacter.h"
#include "Blueprint/UserWidget.h"
UScopeComponent::UScopeComponent()
{
}
// Called when the game starts
void UScopeComponent::BeginPlay()
{
	Super::BeginPlay();
	if (wZoomUI)
	{
		ZoomUI = CreateWidget<UUserWidget>(GetWorld(), wZoomUI);
	}
	// ...
}

void UScopeComponent::Aim()
{
	if (ValidateEquippedWeapon() && !bIsAiming)
	{
		UAimingComponent::Aim();
		bIsAiming = true;
		Owner->OwningPlayer->GetFirstPersonCameraComponent()->FieldOfView /= ZoomAmount;
		Owner->FindComponentByClass<UWeaponBarrelComponent>()->FireLocation = Camera;
		Owner->SetActorHiddenInGame(true);
		if (ZoomUI)
		{
			ZoomUI->AddToViewport();
		}
	}
}

void UScopeComponent::StopAim()
{
	if (ValidateEquippedWeapon() && bIsAiming)
	{
		bIsAiming = false;
		Owner->OwningPlayer->GetFirstPersonCameraComponent()->FieldOfView *= ZoomAmount;
		Owner->FindComponentByClass<UWeaponBarrelComponent>()->FireLocation = Muzzle;
		Owner->SetActorHiddenInGame(false);
		if (ZoomUI)
		{
			ZoomUI->RemoveFromViewport();
		}
	}
}

bool UScopeComponent::ValidateEquippedWeapon()
{
	return Owner && Owner->OwningPlayer && Owner->OwningPlayer->EquippedWeapon == Owner;
}
