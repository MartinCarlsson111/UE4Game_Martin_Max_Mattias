#pragma once

#include "CoreMinimal.h"
#include "../BulletType.h"
#include "../BulletBase.h"
#include "Components/ActorComponent.h"
#include "BulletComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UE4GAME_API UBulletComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Bullet)
	TEnumAsByte<EBulletType> BulletType;

	//Used to spawn multiple projectiles per shot, used for Shotgun shells, which spawns multiple projectiles from one shell.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
	int ProjectilesPerBullet = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
	float Damage = 1.0f;

	//this property is used for Hitscan types, determining how long the linetrace for the hitscan will be.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
	float Range = 5000.0f;

	//if this is enabled, a hitscan bullet will penetrate through objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
	bool bShouldPenetrateHits = false;

	//If bShouldPenetrateHits is true, this will determine how much damage is lost each time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
	float DamageLossPerHit = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
	TSubclassOf<ABulletBase> SolidProjectileType;

	//This Particle system will be spawned at the OnHit Location if the Bullet uses Hitscan.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
	UParticleSystem* OnHitParticleSystem;

	void BeginPlay() override;

};