#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../BulletBase.h"
#include "AmmoComponent.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FMagazines
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int MagazineSize = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int NAmmoPerUse = 1;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class UE4GAME_API UAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//If this function is implemented in Blueprint, user should call OnOutOfAmmo this function returns false.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Ammo)
	bool IsAmmoAvailable();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Ammo)
	void UseAmmo();

	UFUNCTION(BlueprintCallable, Category = Ammo)
	int GetCurrentAmmoCount();

	UFUNCTION(BlueprintNativeEvent, Category = Ammo)
	void Reload(int AmountToReload = 1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TArray<FMagazines> Magazines;

	FMagazines CurrentMagazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int CurrentAmmoCount = 20;

	//This function is called if IsAmmoAvailable returns false in the base implementation
	UFUNCTION(BlueprintNativeEvent, Category = Ammo)
	void OnOutOfAmmo();
};
