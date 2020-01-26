// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE4GameCharacter.h"
#include "UE4GameProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "FirearmSystem/WeaponBase.h"
#include "Interactable_Interface.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);
AUE4GameCharacter::AUE4GameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
}

void AUE4GameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AUE4GameCharacter::Interact()
{
	FHitResult Hit;
	float RayLength = 500;
	FVector StartLocation = FirstPersonCameraComponent->GetComponentLocation();
	FVector EndLocation = StartLocation + (FirstPersonCameraComponent->GetForwardVector() * RayLength);
	FCollisionQueryParams CollisionParameters(FName(TEXT("TraceGround")), false, this);
	GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECollisionChannel::ECC_WorldStatic, CollisionParameters);
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 2, 5, 1.f);
	if (Hit.Actor != nullptr)
	{
		IInteractable_Interface* HitInteractable = Cast<IInteractable_Interface>(Hit.Actor);
		if (HitInteractable) {
			Cast<IInteractable_Interface>(Hit.Actor)->Interact_Implementation(this);
		}
	}
}
void AUE4GameCharacter::EquipWeapon(AWeaponBase* weapon)
{
	if (EquippedWeapon)
	{
		EquippedWeapon->SetActorHiddenInGame(true);
	}
	weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, "GripPoint");
	if (Mesh1P->bHiddenInGame)
	{
		Mesh1P->SetHiddenInGame(false, false);
	}
	EquippedWeapon = weapon;
	Weapons.Add(EquippedWeapon);
	EquippedWeaponIndex = Weapons.Num() - 1;
}
void AUE4GameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AUE4GameCharacter::OnFirePress);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AUE4GameCharacter::OnFireRelease);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AUE4GameCharacter::Interact);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AUE4GameCharacter::Reload);
	PlayerInputComponent->BindAction("CycleWeaponModes", IE_Pressed, this, &AUE4GameCharacter::CycleWeaponModes);

	PlayerInputComponent->BindAxis("ScrollWheel", this, &AUE4GameCharacter::ScrollWheel);
	PlayerInputComponent->BindAxis("MoveForward", this, &AUE4GameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUE4GameCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);


}

void AUE4GameCharacter::PlayAnimation(UAnimMontage* animation)
{
	if (animation)
	{
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(animation, 1.f);
		}
	}
}

void AUE4GameCharacter::OnFirePress()
{
	if (EquippedWeapon) { EquippedWeapon->OnFire(); }
	
}

void AUE4GameCharacter::OnFireRelease()
{
	if(EquippedWeapon) {
		EquippedWeapon->OnStopFire();
	}
}



void AUE4GameCharacter::Reload()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->OnReload();
	}
}

void AUE4GameCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AUE4GameCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AUE4GameCharacter::ChangeWeapon(float index)
{
	if (ValidateWeapon(index)) 
	{ 
		OnSwitchWeapon.Broadcast();
		EquippedWeapon->SetActorHiddenInGame(true);
		EquippedWeapon = Weapons[index]; 
		EquippedWeapon->SetActorHiddenInGame(false);
		EquippedWeaponIndex = index;
	}
}

void AUE4GameCharacter::CycleWeaponModes()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->CycleWeaponModes();
	}
}

void AUE4GameCharacter::ScrollWheel(float val)
{
	if (val < 0) 
	{
		EquippedWeaponIndex--;
		if (EquippedWeaponIndex < 0) EquippedWeaponIndex = Weapons.Num() - 1;
	}
	if (val > 0) 
	{
		EquippedWeaponIndex++;
		if (EquippedWeaponIndex >= Weapons.Num()) EquippedWeaponIndex = 0;
	}
	if (val != 0) 
	{
		ChangeWeapon(EquippedWeaponIndex);
	}
}

bool AUE4GameCharacter::ValidateWeapon(float WeaponIndex)
{
	if (WeaponIndex >= 0)
	{
		return WeaponIndex < Weapons.Num();
	}
	return false;
}
