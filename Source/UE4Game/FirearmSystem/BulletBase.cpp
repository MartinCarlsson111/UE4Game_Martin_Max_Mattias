
#include "BulletBase.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DamageableComponent.h"
ABulletBase::ABulletBase()
{

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Projectile Mesh");
}

UStaticMeshComponent* ABulletBase::GetProjectileMesh()
{
	return ProjectileMesh;
}


void ABulletBase::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeTime);
	Launch();

}

void ABulletBase::CreateDebugLocator(FVector Location, int damage)
{
	if (DebugLocator)
	{
		FRotator rotate = GetActorRotation();
		rotate -= {0, 90, 0};
		const FRotator SpawnRotation = rotate;
		const FVector SpawnLocation = Location;
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AHitLocator* locator = GetWorld()->SpawnActor<AHitLocator>(DebugLocator, SpawnLocation, SpawnRotation, ActorSpawnParams);
		locator->GetText()->SetText(FString::FromInt(damage));
	}
}

void ABulletBase::CreateDebugLocator(FVector Location, AActor* AttachmentActor, int damage)
{
	if (DebugLocator)
	{
		FRotator rotate = GetActorRotation();
		rotate -= {0, 90, 0};
		const FRotator SpawnRotation = rotate;
		const FVector SpawnLocation = Location;
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AHitLocator* locator = GetWorld()->SpawnActor<AHitLocator>(DebugLocator, SpawnLocation, SpawnRotation, ActorSpawnParams);
		locator->AttachToActor(AttachmentActor, FAttachmentTransformRules::KeepWorldTransform);
		locator->GetText()->SetText(FString::FromInt(damage));
		
	}
}

void ABulletBase::Launch()
{
	if (ProjectileMesh->GetStaticMesh())
	{
		ProjectileMesh->SetSimulatePhysics(true);
		ProjectileMesh->SetWorldRotation(GetActorRotation());
		ProjectileMesh->SetWorldLocation(GetActorLocation());
		ProjectileMesh->SetEnableGravity(Gravity);
		FVector LaunchDirection = ProjectileMesh->GetRightVector() * Force;
		ProjectileMesh->AddImpulse(LaunchDirection, NAME_None, true);
		ProjectileMesh->OnComponentHit.AddDynamic(this, &ABulletBase::OnHit);
	}
}

void ABulletBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Hit.Actor != nullptr) {

		UDamageableComponent* other = Hit.Actor->FindComponentByClass<UDamageableComponent>();
		if (other)
		{
			other->Damage(HitDamage);
			CreateDebugLocator(Hit.Location, HitDamage);
		}
		else CreateDebugLocator(Hit.Location, OtherActor, HitDamage);
	}
	else CreateDebugLocator(Hit.Location, HitDamage);
	HitsBeforeDestroyed--;
	if (HitsBeforeDestroyed < 1 && HitsBeforeDestroyed > -1)
	{
		SetLifeSpan(TimeAliveAfterBounces);
		ProjectileMesh->SetSimulatePhysics(!StopsMovingAfterCollision);
	}
}
