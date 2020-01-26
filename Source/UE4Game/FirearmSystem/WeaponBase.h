// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponMode.h"
#include "../Interactable_Interface.h"
#include "WeaponBase.generated.h"
class AUE4GameCharacter;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPickedUp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnfire);

UCLASS(ClassGroup = (FireArmSystem), Abstract, hidecategories = (LOD, Actor, Cooking, Input))
class UE4GAME_API AWeaponBase : public AActor, public IInteractable_Interface
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent *GunMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = FireEffect)
	class UParticleSystemComponent *OnFireEffect;

public:
	AWeaponBase();
	UPROPERTY()

	FPickedUp PickedUp;

	FOnfire FiringWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, Meta = (ToolTip = "The sound played when a bullet is fired"))
	class USoundBase *FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, Meta = (ToolTip = "The sound played upon reload"))
	class USoundBase *ReloadSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, Meta = (ToolTip = "The sound played upon pickup"))
	class USoundBase *PickupSound;

protected:

	UPROPERTY()
	TArray<FWeaponMode> WeaponModes;

	UPROPERTY()
	int CurrentWeaponModeIndex = 0;

public:
	UFUNCTION(BlueprintCallable, Category = WeaponMode)
	void AddWeaponMode(
		UAmmoComponent *WeaponAmmoComponent,
		UWeaponTriggerComponent *WeaponTriggerComponent,
		UWeaponBarrelComponent *WeaponBarrelComponent,
		UBulletComponent *WeaponBulletComponent);

	virtual void Interact_Implementation(ACharacter *PickupActor) override;

	void OnReload();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UE4 Character", Meta = (ToolTip = "The player who owns the weapon"))
	AUE4GameCharacter *OwningPlayer;

	void PlaySound(USoundBase *Sound);

	void CycleWeaponModes();

	UFUNCTION(BlueprintNativeEvent)
	void Firing();
	void Firing_Implementation(){};

	UFUNCTION(BlueprintCallable, Category = "Weapon", Meta = (ToolTip = "Executes the start of the firing mechanic for this weapon"))
	void OnFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon", Meta = (ToolTip = "Finishes the firing of this weapon"))
	void OnStopFire();
};
