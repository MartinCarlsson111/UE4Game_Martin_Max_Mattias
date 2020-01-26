// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "AOEComponent.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTick);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4GAME_API UAOEComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UAOEComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AOEShape, Meta = (ToolTip = "The damage applied to damageable components inside the hitbox every time the damage ticks, irrelevant if tick is not enabled"))
	int TickDamage = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AOEShape, Meta = (ToolTip = "The damage applied to damageable components inside the hitbox, only activates when projectile collides with other and triggers on impact is true"))
		int ImpactDamage = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AOEShape, Meta = (ToolTip = "Should the boxcollider apply damage on projectile impact?"))
	bool bTriggersOnImpact = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AOEShape, Meta = (ToolTip = "Should the boxcollider tick damage as its flying?"))
	bool bTickableDamage = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AOEShape, Meta = (ToolTip = "How often should the collider apply damage? Irrelevant if tick damage is false"))
		float TickRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AOEShape, Meta = (ToolTip = "How big the aoe is"))
		float AOERadius = 250.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AOEShape, Meta = (ToolTip = "Whether or not to display the debug spheres"))
		bool bDebug = true;
	//Bound to the owning projectiles mesh onhit event
	UFUNCTION(BlueprintCallable)
		void Impact(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	//An event callable in blueprints to allow designers a time to add stuff to the aoe
	UPROPERTY(BlueprintAssignable)
	FTick OnTick;
	//A function that does the damage tick with the specified damage
	UFUNCTION(BlueprintCallable)
		void OverrideDamageTick(int OverrideDamage);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	void DamageTick();
	FTimerHandle TickDamageTimerHandle;
public:	
	// Called every frame

		
};
