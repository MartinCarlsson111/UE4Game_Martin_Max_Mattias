#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"
class AWeaponBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAiming);
UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4GAME_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAimingComponent();
	
	UFUNCTION()
	virtual void Aim() 
	{ 
		if (Aiming.IsBound())
		{
			Aiming.Broadcast();
		}
	};
	UFUNCTION()
		virtual void StopAim() {};
	//An event to allow designers to elaborate upon aiming
	UPROPERTY(BlueprintAssignable, Category = "Aim", Meta = (ToolTip = "Event called when this weapon is aiming"))
		FAiming Aiming;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	AWeaponBase* Owner;
private:
	//Sets up the bindings so that the functions Aim and StopAim are called at the appropriate times
	UFUNCTION()
		void BindAim();
public:	

		
};
