// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UE4GameCharacter.generated.h"
class AWeaponBase;
class UInputComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSwitchWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReload);
UCLASS(config=Game)
class AUE4GameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;
	
public:
	AUE4GameCharacter();
	UPROPERTY()
	FSwitchWeapon OnSwitchWeapon;
	FReload OnReload;
protected:
	virtual void BeginPlay();
	void Interact();
public:
	/** Sound to play each time we fire */
	
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EquipWeapon(AWeaponBase* weapon);
	/** AnimMontage to play each time we fire */
	AWeaponBase* EquippedWeapon;
	TArray<AWeaponBase*> Weapons;
	
	void PlayAnimation(UAnimMontage* animation);
protected:
	
	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable)
	void OnFirePress();
	UFUNCTION(BlueprintCallable)
	void OnFireRelease();
	UFUNCTION(BlueprintCallable)
	void Reload();
	void MoveForward(float Val);
	void MoveRight(float Val);
	void ChangeWeapon(float index);

	void CycleWeaponModes();
	void ScrollWheel(float val);
	int EquippedWeaponIndex;
	bool ValidateWeapon(float WeaponIndex);
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

