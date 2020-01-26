#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../HitLocator.h"
#include "BulletBase.generated.h"
UCLASS()
class UE4GAME_API ABulletBase : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent *ProjectileMesh;

public:
	ABulletBase();
	UStaticMeshComponent *GetProjectileMesh();
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	TSubclassOf<class AHitLocator> DebugLocator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties", Meta = (ToolTip = "Damage apllied upon hit with damageable object"))
	float HitDamage;
	void CreateDebugLocator(FVector Location, int damage);
	void CreateDebugLocator(FVector Location, AActor *AttachmentActor, int damage);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties", Meta = (ToolTip = "The lifetime of the bullet, -1 if no timer"))
	float LifeTime = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties", Meta = (ToolTip = "The force with which the projectile is launched"))
	float Force = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties", Meta = (ToolTip = "Whether the projectile simulates gravity or not"))
	bool Gravity = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties", Meta = (ToolTip = "Whether the projectile should keep bouncing after collision or not"))
	bool StopsMovingAfterCollision = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties", Meta = (ToolTip = "How long the actor will remain alive after the last hit before destruciton happens"))
	float TimeAliveAfterBounces = 0.1f;
	void Launch();
	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties", Meta = (ToolTip = "How many times the projectile can collide with something else before destroyed"))
	int HitsBeforeDestroyed = 1;
};
