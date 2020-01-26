// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.h"
#include "AimDownSightsComponent.generated.h"

class AWeaponBase;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UE4GAME_API UAimDownSightsComponent : public UAimingComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAimDownSightsComponent();
	AWeaponBase* owner;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Aim", Meta = (ToolTip = "What is the new location based on where the weapon was before?"))
	FVector Location = { 0,0,0 };

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Aim", Meta = (ToolTip = "How much should the weapon rotate upon aiming?"))
	FRotator Rotation = { 0,0,0 };

	void Aim() override;

	void StopAim() override;
public:
};
