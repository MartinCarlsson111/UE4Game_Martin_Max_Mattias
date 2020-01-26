// Fill out your copyright notice in the Description page of Project Settings.


#include "AOEComponent.h"
#include "../BulletBase.h"
#include "DamageableComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
// Sets default values for this component's properties
UAOEComponent::UAOEComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	

	// ...
}

// Called when the game starts
void UAOEComponent::BeginPlay()
{
	Super::BeginPlay();
	if (bTriggersOnImpact)
	{
		ABulletBase* OwningBullet = Cast<ABulletBase>(GetOwner());
		if (OwningBullet)
		{

			OwningBullet->GetProjectileMesh()->OnComponentHit.AddDynamic(this, &UAOEComponent::Impact);
		}
	}
	if (bTickableDamage) GetOwner()->GetWorldTimerManager().SetTimer(TickDamageTimerHandle, this, &UAOEComponent::DamageTick, TickRate, true, 0.0f);
	// ...
	
}
void UAOEComponent::DamageTick()
{
	OverrideDamageTick(TickDamage);
}

void UAOEComponent::OverrideDamageTick(int damageOverride)
{
	OnTick.Broadcast();
	TArray<FHitResult> OutHits;
	FVector SphereLocation = GetOwner()->GetActorLocation();
	FCollisionShape ExplosionCol = FCollisionShape::MakeSphere(AOERadius);
	if(bDebug) DrawDebugSphere(GetWorld(), SphereLocation, ExplosionCol.GetSphereRadius(), 50, FColor::Purple, false, 2);
	if (GetWorld()->SweepMultiByChannel(OutHits, SphereLocation, SphereLocation, FQuat::Identity, ECC_WorldStatic, ExplosionCol))
	{
		for (auto& Hit : OutHits)
		{
			if (Hit.GetActor())
			{
				UDamageableComponent* Damageable = Hit.GetActor()->FindComponentByClass<UDamageableComponent>();
				if (Damageable)
				{
					Damageable->Damage(damageOverride);
				}
			}
		}
	}
}

void UAOEComponent::Impact(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	OverrideDamageTick(ImpactDamage);
}

