// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../WeaponMode.h"

#include "WeaponTriggerComponent.generated.h"


UCLASS( ClassGroup=(Trigger), Blueprintable, BlueprintType, hidecategories = (Tags, AssetUserData, Cooking, Activation, Collision))
class UE4GAME_API UWeaponTriggerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UWeaponTriggerComponent();
	void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = OnFire)
	void OnFire(FWeaponMode WeaponMode);

	UFUNCTION(BlueprintNativeEvent, Category = OnStopFire)
	void OnStopFire(FWeaponMode WeaponMode);

	//The current state of the Trigger
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Trigger)
	bool FireState = false;

};
