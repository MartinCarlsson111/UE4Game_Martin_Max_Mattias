#include "AimDownSightsComponent.h"
#include "../WeaponBase.h"
// Sets default values for this component's properties
UAimDownSightsComponent::UAimDownSightsComponent()
{
}


// Called when the game starts
void UAimDownSightsComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UAimDownSightsComponent::Aim()
{
	UAimingComponent::Aim();
	Owner->AddActorLocalOffset(Location);
	Owner->AddActorLocalRotation(Rotation);
}

void UAimDownSightsComponent::StopAim()
{
	Owner->SetActorRelativeLocation({ 0,0,0 });
	Owner->SetActorRelativeRotation({ 0,0,0 });;
}

