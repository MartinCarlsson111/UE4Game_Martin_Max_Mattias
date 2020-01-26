// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "BulletBase.h"
#include "BulletType.generated.h"

UENUM(BlueprintType, Category = BulletType)
enum EBulletType
{
	HitScan,
	SolidProjectile
};
