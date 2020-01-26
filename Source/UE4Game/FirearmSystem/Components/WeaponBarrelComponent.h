// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletComponent.h"
#include "Components/ActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponBarrelComponent.generated.h"
UENUM(BlueprintType, Category = WeaponBarrel)
enum EFireLocation {
	Muzzle, Camera
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShoot);
UCLASS( ClassGroup=(FirearmSystem), meta=(BlueprintSpawnableComponent), BlueprintType, Blueprintable, hideCategories = (Tags, Cooking, AssetUserData, Collision, Sockets))
class UE4GAME_API UWeaponBarrelComponent : public UActorComponent
{
	GENERATED_BODY()
	USkeletalMeshComponent* Gun;
public:
	void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FShoot OnShoot;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = OnFire)
	void OnFire(UBulletComponent* BulletToShoot);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gameplay")
	float BulletSpreadDegrees = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gameplay")
	FVector BulletSpreadFunction(const FVector& LookDirection);

	//Spawn offset, all shots will be fired with this spawn offset in the direction of the muzzle or camera.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gameplay")
	int SpawnOffset = 250;

	//This enables debug features, enables hitscan debug line, and if Debug Locator is set, also spawns debug locator at hit position
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug")
	bool IsDebugEnabled = false;

	//this determines from what position the weapon fires. 
	//Either Muzzle, which looks for a bone in the skeletal mesh of the skin called "Muzzle" to shoot from in the direction of the bone.
	//Or Camera, which shoots from camera position in the direction of the camera.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	TEnumAsByte<EFireLocation> FireLocation = Muzzle;
	
	void CreateDebugLocator(const FVector& Location, const AActor* AttachmentActor, float Damage);

	void FireHitScan(const FVector& StartLocation, const FRotator& Direction, UBulletComponent* BulletToShoot);

	void FireSolidProjectile(const FVector& Location, FRotator Direction, UBulletComponent* BulletToShoot);

	//Can be used to display information about each hit.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	TSubclassOf<class AHitLocator> DebugLocator;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = OnHit)
	void OnProjectileHit(const FVector HitLocation, const FVector HitNormal, const float DamageDone, const float Range, UParticleSystem* ParticleSystemToSpawn);
};
