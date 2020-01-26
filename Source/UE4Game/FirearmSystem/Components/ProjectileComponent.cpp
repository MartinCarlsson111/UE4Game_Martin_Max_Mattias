// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileComponent.h"
#include "DamageableComponent.h"
#include "../BulletBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UProjectileComponent::UProjectileComponent()
{
}

// Called when the game starts
void UProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}

void UProjectileComponent::Launch()
{
	if (Cast<ABulletBase>(GetOwner()))
	{
		UStaticMeshComponent* Projectile = Cast<ABulletBase>(GetOwner())->GetProjectileMesh();
		if (Projectile->GetStaticMesh())
		{
			Projectile->SetSimulatePhysics(true);
			Projectile->SetWorldRotation(GetOwner()->GetActorRotation());
			Projectile->SetWorldLocation(GetOwner()->GetActorLocation());
			Projectile->SetEnableGravity(Gravity);
			FVector LaunchDirection = Projectile->GetRightVector() * Force;
			Projectile->AddImpulse(LaunchDirection, NAME_None, true);
			Projectile->OnComponentHit.AddDynamic(this, &UProjectileComponent::OnHit);
		}
	}
}

void UProjectileComponent::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ABulletBase* owner = Cast<ABulletBase>(GetOwner());
	if (owner) 
	{
		owner->CreateDebugLocator(Hit.Location, OtherActor, owner->HitDamage);
	}
	UDamageableComponent* other = Hit.Actor->FindComponentByClass<UDamageableComponent>();
	if (other) other->Damage(owner->HitDamage);
	HitsBeforeDestroyed--;
	if (HitsBeforeDestroyed < 1 && HitsBeforeDestroyed > -1) GetOwner()->SetLifeSpan(0.001f);
}

