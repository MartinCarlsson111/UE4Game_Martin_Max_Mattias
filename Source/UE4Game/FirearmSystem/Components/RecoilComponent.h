// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RecoilComponent.generated.h"
class AWeaponBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRecoil);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4GAME_API URecoilComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, Meta = (ToolTip = "For how long will the recoil will be applied"))
	float RecoilDuration = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, Meta = (ToolTip = "How much recoil to apply"))
	float RecoilStrength = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, Meta = (ToolTip = "Does recoil get applied to the Pitch of the controller?"))
	bool bIsRecoilAppliedInPitch = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, Meta = (ToolTip = "Does recoil get applied to the Yaw of the controller"))
	bool bIsRecoilAppliedInYaw = false;

	//This will start the Recoil timer which calls TickRecoil depending on RecoilRate
	UFUNCTION(BlueprintCallable)
	void AddRecoil();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, Meta = (ToolTip = "How much knockback force will be applied to the player upon firing, will launch player forward if negative"))
	float KnockbackForce = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, Meta = (ToolTip = "If the recoil should be called automaticly upon firing or if you want to call it from blueprints"))
	bool bManualCallOfRecoil = false;

	UPROPERTY(BlueprintAssignable, Category = "Properties", Meta = (ToolTip = "Event called when recoil is applied"))
	FRecoil OnRecoil;

	//This method applies the rotation to the controller.
	//Override this implementation to create your own recoil pattern.
	UFUNCTION(BlueprintNativeEvent, Category = Recoil)
	void RecoilFunction();

	//This method applies impulse to the controller.
	//Override this implementation to create your own knockback pattern.
	UFUNCTION(BlueprintNativeEvent, Category = Knockback)
	void KnockbackFunction();

protected:
	AWeaponBase* Owner;

	virtual void BeginPlay() override;

	float RecoilAccu = 0;

	FTimerHandle TimerHandle;
		
};
