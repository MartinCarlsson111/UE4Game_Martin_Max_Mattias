// Fill out your copyright notice in the Description page of Project Settings.

#include "RecoilComponent.h"
#include "../WeaponBase.h"
#include "../../UE4GameCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WeaponBarrelComponent.h"


void URecoilComponent::AddRecoil()
{
	Owner = Cast<AWeaponBase>(GetOwner());
	if (Owner->OwningPlayer)
	{
		RecoilFunction();
		KnockbackFunction();
		OnRecoil.Broadcast();
	}
}

void URecoilComponent::RecoilFunction_Implementation()
{
	if (bIsRecoilAppliedInPitch)
	{
		Owner->OwningPlayer->AddControllerPitchInput(-(RecoilStrength));
	}
	if (bIsRecoilAppliedInYaw)
	{
		Owner->OwningPlayer->AddControllerYawInput(RecoilStrength);
	}
}

void URecoilComponent::KnockbackFunction_Implementation()
{
	if (Owner->OwningPlayer)
	{
		Owner->OwningPlayer->GetCharacterMovement()->AddImpulse(Owner->GetActorRightVector() * -KnockbackForce, true);
	}
}

void URecoilComponent::BeginPlay()
{
	Super::BeginPlay();
	AWeaponBase *owner = Cast<AWeaponBase>(GetOwner());
	if (!bManualCallOfRecoil && owner)
	{
		UWeaponBarrelComponent* WeaponBarrel = Cast<UWeaponBarrelComponent>(GetOwner()->GetComponentByClass(UWeaponBarrelComponent::StaticClass()));
		if (WeaponBarrel)
		{
			WeaponBarrel->OnShoot.AddDynamic(this, &URecoilComponent::AddRecoil);
		}
	}
}
