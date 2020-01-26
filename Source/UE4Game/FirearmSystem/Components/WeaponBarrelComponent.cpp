#include "WeaponBarrelComponent.h"
#include "DrawDebugHelpers.h"
#include "DamageableComponent.h"
#include "../../UE4GameCharacter.h"
#include "../WeaponBase.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "RecoilComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

void UWeaponBarrelComponent::BeginPlay()
{
	Super::BeginPlay();
	Gun = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
}

void UWeaponBarrelComponent::OnFire_Implementation(UBulletComponent *BulletToShoot)
{
	OnShoot.Broadcast();
	FVector Spawn;
	FRotator Rotation;
	AWeaponBase *OwningWeapon = Cast<AWeaponBase>(GetOwner());
	OwningWeapon->PlaySound(OwningWeapon->FireSound);
	if (FireLocation == Muzzle)
	{
		Spawn = Gun->GetSocketLocation("Muzzle") + GetOwner()->GetActorRightVector() * SpawnOffset;
		Rotation = Gun->GetRightVector().Rotation();
	}
	else if (FireLocation == EFireLocation::Camera)
	{
		UCameraComponent *CameraComponent = OwningWeapon->OwningPlayer->GetFirstPersonCameraComponent();
		Spawn = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * SpawnOffset;
		Rotation = CameraComponent->GetComponentRotation();
		//Rotation -= {0, 90, 0}; // TODO: Test if camera needs rot
	}

	if (BulletToShoot->BulletType == EBulletType::HitScan)
	{
		FireHitScan(Spawn, Rotation, BulletToShoot);
	}
	else
	{

		FireSolidProjectile(Spawn, Rotation, BulletToShoot);
	}
}

FVector UWeaponBarrelComponent::BulletSpreadFunction_Implementation(const FVector &LookDirection)
{
	return UKismetMathLibrary::RandomUnitVectorInConeInDegrees(LookDirection, BulletSpreadDegrees);
}

void UWeaponBarrelComponent::CreateDebugLocator(const FVector &Location, const AActor *AttachmentActor, float Damage)
{
	if (DebugLocator)
	{
		const FRotator SpawnRotation = {0, 0, 0};
		const FVector SpawnLocation = Location;
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AHitLocator>(DebugLocator, SpawnLocation, SpawnRotation, ActorSpawnParams)->GetText()->SetText(FString::SanitizeFloat(Damage));
	}
}

void UWeaponBarrelComponent::FireHitScan(const FVector &StartLocation, const FRotator &Direction, UBulletComponent *BulletToShoot)
{
	//TODO: Expose this to designer, so they can choose what to collide with
	//TODO: Let designer choose, if bullet should go through enemy
	//TODO: Let designer choose what happens when bullets go through enemy
	FCollisionQueryParams CollisionParameters(FName(TEXT("Bullet Hitscan")), false, GetOwner());
	CollisionParameters.bTraceComplex = true;
	CollisionParameters.bFindInitialOverlaps = false;

	FCollisionObjectQueryParams Params;
	Params.AddObjectTypesToQuery(ECC_Pawn);
	Params.AddObjectTypesToQuery(ECC_WorldStatic);
	Params.AddObjectTypesToQuery(ECC_WorldDynamic);

	for (int j = 0; j < BulletToShoot->ProjectilesPerBullet; j++)
	{

		FVector EndLocation = StartLocation + (BulletSpreadFunction(Direction.Vector()) * BulletToShoot->Range);
		TArray<FHitResult> Hits;
		GetWorld()->LineTraceMultiByObjectType(Hits, StartLocation, EndLocation, Params, CollisionParameters);

		if (IsDebugEnabled)
		{
			DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 2, 5, 1.f);
		}

		for (int i = 0; i < Hits.Num(); i++)
		{
			if (Hits[i].Actor != nullptr)
			{
				FVector Dir = (StartLocation - Hits[i].Location);
				if (Dir.Normalize())
				{
					UDamageableComponent *Other = Cast<UDamageableComponent>(Hits[i].Actor->GetComponentByClass(UDamageableComponent::StaticClass()));
					if (Other)
					{
						float DamageLost = BulletToShoot->DamageLossPerHit * i;
						if (DamageLost > BulletToShoot->Damage)
						{
							DamageLost = 0;
						}
						float DamageDealt = BulletToShoot->Damage - DamageLost;

						Other->Damage(DamageDealt);

						if (IsDebugEnabled)
						{
							CreateDebugLocator(Hits[i].Location + Dir, Hits[i].GetActor(), DamageDealt);
						}
						
						OnProjectileHit(Hits[i].ImpactPoint, Hits[i].ImpactNormal, DamageDealt, Hits[i].Distance, BulletToShoot->OnHitParticleSystem);
					}
				}
			}
			if (!BulletToShoot->bShouldPenetrateHits)
			{
				break;
			}
		}
	}
}

void UWeaponBarrelComponent::FireSolidProjectile(const FVector &Location, FRotator Direction, UBulletComponent *BulletToShoot)
{
	if (FireLocation != EFireLocation::Camera)
	{
		Direction -= {0, 90, 0};
	}

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	for (int j = 0; j < BulletToShoot->ProjectilesPerBullet; j++)
	{

		GetWorld()->SpawnActor<ABulletBase>(BulletToShoot->SolidProjectileType, Location, Direction, ActorSpawnParams);
	}
}

void UWeaponBarrelComponent::OnProjectileHit_Implementation(const FVector HitLocation, const FVector HitNormal, const float DamageDone, const float Range, UParticleSystem *ParticleSystemToSpawn)
{
	if (ParticleSystemToSpawn != NULL)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystemToSpawn, HitLocation, HitNormal.Rotation(), true);
	}

	if (IsDebugEnabled)
	{
	}
}
