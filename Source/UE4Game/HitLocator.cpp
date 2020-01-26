// Fill out your copyright notice in the Description page of Project Settings.


#include "HitLocator.h"
#include "Components/DecalComponent.h"

// Sets default values
AHitLocator::AHitLocator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Decal = CreateDefaultSubobject<UDecalComponent>("Hit Symbol");
	Text = CreateDefaultSubobject<UTextRenderComponent>("Hit Number");
}

// Called when the game starts or when spawned
void AHitLocator::BeginPlay()
{
	Super::BeginPlay();
	Text->AttachToComponent(Decal, FAttachmentTransformRules::SnapToTargetIncludingScale);
	Text->SetRelativeLocation({10,0,0});
	SetLifeSpan(LifeSpan);
}


