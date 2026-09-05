// Copyright Tijmen Verhoef 2026


#include "Actors/IdiomExpressInteractableActor.h"

#include "Components/SphereComponent.h"
#include "Characters/IdiomExpressCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogIdiomExpressInteractableActor, Log, Log);

AIdiomExpressInteractableActor::AIdiomExpressInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	// Create interaction region
	ActorCollision = CreateDefaultSubobject<USphereComponent>("ActorCollision");
	ActorCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ActorCollision->SetCollisionProfileName("BlockAll");
	SetRootComponent(ActorCollision);
	
	// Create actor mesh
	ActorMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ActorMesh");
	ActorMesh->SetupAttachment(ActorCollision);
	
	// Create interaction region
	InteractionRegion = CreateDefaultSubobject<USphereComponent>("InteractionRegion");
	InteractionRegion->SetupAttachment(ActorCollision);
	
	// Set up interaction region overlap detection
	InteractionRegion->OnComponentBeginOverlap.AddDynamic(this, &AIdiomExpressInteractableActor::OnEnterInteractionRegion);
	InteractionRegion->OnComponentEndOverlap.AddDynamic(this, &AIdiomExpressInteractableActor::OnLeaveInteractionRegion);
}

void AIdiomExpressInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AIdiomExpressInteractableActor::OnEnterInteractionRegion(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	UE_LOGF(LogIdiomExpressInteractableActor, Log,
		"Actor %ls entered interactable region for %ls",
		*OtherActor->GetName(),
		*GetName()
	);
	
	// Check if the actor is a character
	if (auto* Character = Cast<AIdiomExpressCharacter>(OtherActor))
	{
		// Notify character that it entered an interactable region
		Character->OnEnterInteractionRegion();
	}
}

void AIdiomExpressInteractableActor::OnLeaveInteractionRegion(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex
)
{
	UE_LOGF(LogIdiomExpressInteractableActor, Log,
		"Actor %ls left interactable region for %ls",
		*OtherActor->GetName(),
		*GetName()
	);
	
	// Check if the actor is a character
	if (auto* Character = Cast<AIdiomExpressCharacter>(OtherActor))
	{
		// Notify character that it left an interactable region
		Character->OnLeaveInteractionRegion();
	}
}

void AIdiomExpressInteractableActor::OnInteraction(class AIdiomExpressCharacter* Character)
{
	OnInteractionEvent(Character);
}
