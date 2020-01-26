// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileComponent.generated.h"

class UDamageable_Interface;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4GAME_API UProjectileComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UProjectileComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
		float Force = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
		bool Gravity = true;
	void Launch();
	UFUNCTION(BlueprintCallable)
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
		int HitsBeforeDestroyed = 1;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

		
};
