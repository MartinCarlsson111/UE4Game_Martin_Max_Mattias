// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDying);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTakeDamage);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4GAME_API UDamageableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageableComponent();
	UFUNCTION(BlueprintCallable)
		void Damage(int amount);
	virtual void Damage_Implementation(int amount) {}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", Meta = (ToolTip = "How many hitpoints the target can lose before it dies"))
		int HitPoints = 10;
	UPROPERTY(BlueprintAssignable, Category = "Properties", Meta = (ToolTip = "Event called when the object has lost all its hitpoints and is starting to be destroyed"))
		FDying Dying;
	UPROPERTY(BlueprintAssignable, Category = "Properties", Meta = (ToolTip = "Event called when the object takes any damage"))
		FOnTakeDamage OnTakeDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", Meta = (ToolTip = "How long time it takes for the object to destroy after it has lost all it's hitpoints"))
		float DeathTime = 0.01f;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

		
};
