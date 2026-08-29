// Copyright Tijmen Verhoef 2026


#include "Actors/IdiomExpressInteractableActor.h"

#include "Components/SphereComponent.h"

AIdiomExpressInteractableActor::AIdiomExpressInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	// Create interaction region
	InteractionRegion = CreateDefaultSubobject<USphereComponent>("InteractionRegion");
	SetRootComponent(InteractionRegion);
	
	// Create actor mesh
	ActorMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ActorMesh");
	ActorMesh->SetupAttachment(InteractionRegion);
}

void AIdiomExpressInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}
