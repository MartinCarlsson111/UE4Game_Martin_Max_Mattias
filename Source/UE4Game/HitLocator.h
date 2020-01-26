// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "HitLocator.generated.h"
class UTextRenderComponent;
UCLASS()
class UE4GAME_API AHitLocator : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh, Meta = (ToolTip = "What decal should be displayed?"))
	class UDecalComponent* Decal;
public:	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UTextRenderComponent* Text;
	// Sets default values for this actor's properties
	AHitLocator();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ToolTip = "How long the decal is displayed"))
		float LifeSpan = 20;
	UTextRenderComponent* GetText() { return Text; };
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
};
