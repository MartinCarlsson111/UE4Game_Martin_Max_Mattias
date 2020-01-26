// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	

}


void ASpawnPoint::RemoveEnemyFromList(AEnemyCharacter* enemytoremove)
{
	if (Enemies.Find(enemytoremove))
	{ 
		Enemies.Remove(enemytoremove); 
	}
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	Enemies.Add(nullptr);
	if(bEnemiesRespawn) GetWorldTimerManager().SetTimer(SpawnerTimerHandle, this, &ASpawnPoint::SpawnEnemy, TickRate, true);
	else 
	{
		for (int i = 0; i < EnemiesToSpawn; i++)
		{
			SpawnEnemy();
		}
	}
}

void ASpawnPoint::SpawnEnemy()
{
	if (Enemies.Num() < EnemiesToSpawn + 1) 
	{
		const FRotator SpawnRotation = GetActorRotation();
		const FVector SpawnLocation = GetActorLocation();
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		Enemies.Add(GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, SpawnLocation, SpawnRotation, ActorSpawnParams));
		Enemies.Last()->OwningSpawnPoint = this;
	}
}
