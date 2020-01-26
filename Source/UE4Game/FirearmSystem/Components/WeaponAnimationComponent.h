// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponAnimationComponent.generated.h"

class AWeaponBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4GAME_API UWeaponAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponAnimationComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (ToolTip = "The animation played when the weapon is fired"))
		class UAnimMontage* FireAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (ToolTip = "The animation played when the weapon is reloading"))
		class UAnimMontage* ReloadAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (ToolTip = "The animation played when the weapon is picked up"))
		class UAnimMontage* PickUpAnimation;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	AWeaponBase* Owner;
	bool bHasBoundReload = false;
	UFUNCTION(BlueprintCallable)
	void PlayFireAnimation();
	UFUNCTION(BlueprintCallable)
	void PlayReloadAnimation();
	UFUNCTION(BlueprintCallable)
	void PlayPickUpAnimation();

		
};
