// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include "../WeaponBase.h"
#include "../../UE4GameCharacter.h"
#include "Components/InputComponent.h"
// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// ...
}

// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AWeaponBase>(GetOwner());
	if (Owner)
	{
		Owner->PickedUp.AddDynamic(this, &UAimingComponent::BindAim);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Did not find owning weapon!"));
	// ...
}

void UAimingComponent::BindAim()
{
	Owner->OwningPlayer->InputComponent->BindAction("Aim", IE_Pressed, this, &UAimingComponent::Aim);
	Owner->OwningPlayer->InputComponent->BindAction("Aim", IE_Released, this, &UAimingComponent::StopAim);
	Owner->OwningPlayer->OnSwitchWeapon.AddDynamic(this, &UAimingComponent::StopAim);
}