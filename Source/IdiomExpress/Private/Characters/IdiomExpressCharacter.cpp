// Copyright Tijmen Verhoef 2026


#include "Characters/IdiomExpressCharacter.h"

#include "Actors/IdiomExpressInteractableActor.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/IdiomExpressInteractionComponent.h"

#define CHARACTER_INTERACTION_LINE_TRACE_LENGTH 1'000.0F

DEFINE_LOG_CATEGORY_STATIC(LogIdiomExpressCharacter, Log, Log);

AIdiomExpressCharacter::AIdiomExpressCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Get player capsule
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	
	// Set up camera component
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	PlayerCamera->SetupAttachment(Capsule);
	PlayerCamera->SetEnableFirstPersonScale(true);
	PlayerCamera->SetEnableFirstPersonFieldOfView(true);
	PlayerCamera->bUsePawnControlRotation = true;
	
	// Set up interaction component
	InteractionComponent = CreateDefaultSubobject<UIdiomExpressInteractionComponent>("InteractionComponent");
}

void AIdiomExpressCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AIdiomExpressCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Handle aim test line trace if in interactable region
	// TODO

	// Handle player interaction input
	if (auto* InteractionComp = GetInteractionComponent())
	{
		// Consume interacting value
		const bool bIsInteracting = InteractionComp->ConsumeIsInteractingValue();
		if (bIsInteracting)
		{
			// Send interaction raycast into world
			DoInteractionLineTrace();
		}
	}
}

void AIdiomExpressCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AIdiomExpressCharacter::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	// Get player camera location and rotation :)
	OutLocation = PlayerCamera->GetComponentLocation();
	OutRotation = PlayerCamera->GetComponentRotation();
}

void AIdiomExpressCharacter::Interact()
{
	// Set the internal interacting value
	if (auto* InteractionComp = GetInteractionComponent()) {
		InteractionComp->SetIsInteractingValue(true);
	}
}

void AIdiomExpressCharacter::OnEnterInteractionRegion(AIdiomExpressInteractableActor* InteractableActor)
{
	//
}
	
void AIdiomExpressCharacter::OnLeaveInteractionRegion(AIdiomExpressInteractableActor* InteractableActor)
{
	//
}

void AIdiomExpressCharacter::DoAimTestLineTrace()
{
	// Get start and end points for the aim test trace
	FVector ViewOrigin{};
	FRotator ViewDirection{};
	GetActorEyesViewPoint(ViewOrigin, ViewDirection);
	FVector const TraceEndPoint = ViewOrigin + ViewDirection.Vector() * CHARACTER_INTERACTION_LINE_TRACE_LENGTH;
	
	// Get the world for the actor
	UWorld* World = GetWorld();
	check(World);
	
	// Do line trace
	FHitResult TraceResult{};
	UE_LOG(LogIdiomExpressCharacter, Log, TEXT("Performing aim test line trace"));
	if (World->LineTraceSingleByChannel(TraceResult, ViewOrigin, TraceEndPoint, ACTOR_INTERACTION_COLLISION_CHANNEL))
	{
		// Check if the trace is a valid blocking hit
		UE_LOG(LogIdiomExpressCharacter, Log, TEXT("Testing valid blocking hit"));
		if (!TraceResult.IsValidBlockingHit()) {
			return;
		}
		
		// Interact with actor if it is interactable.
		UE_LOG(LogIdiomExpressCharacter, Log, TEXT("Valid blocking hit found"));
		if (auto* InteractableActor = Cast<AIdiomExpressInteractableActor>(TraceResult.GetActor()))
		{			
			// TODO(nemjit001): Enable aim prompt in player HUD
		}
	}
}

void AIdiomExpressCharacter::DoInteractionLineTrace()
{
	// Get start and end points for the interaction trace
	FVector ViewOrigin{};
	FRotator ViewDirection{};
	GetActorEyesViewPoint(ViewOrigin, ViewDirection);
	FVector const TraceEndPoint = ViewOrigin + ViewDirection.Vector() * CHARACTER_INTERACTION_LINE_TRACE_LENGTH;
	
	// Get the world for the actor
	UWorld* World = GetWorld();
	check(World);
	
	// Do line trace	
	FHitResult TraceResult{};
	UE_LOG(LogIdiomExpressCharacter, Log, TEXT("Performing interaction line trace"));	
	if (World->LineTraceSingleByChannel(TraceResult, ViewOrigin, TraceEndPoint, ACTOR_INTERACTION_COLLISION_CHANNEL))
	{		
		// Check if the trace is a valid blocking hit
		UE_LOG(LogIdiomExpressCharacter, Log, TEXT("Testing valid blocking hit"));
		if (!TraceResult.IsValidBlockingHit()) {
			return;
		}
		
		// Interact with actor if it is interactable.
		UE_LOG(LogIdiomExpressCharacter, Log, TEXT("Valid blocking hit found"));
		if (auto* InteractableActor = Cast<AIdiomExpressInteractableActor>(TraceResult.GetActor()))
		{
			UE_LOGF(LogIdiomExpressCharacter, Log,
				"Performing interaction: %ls interacting with %ls",
				*GetName(),
				*InteractableActor->GetName()
			);
			
			// TODO(nemjit001): Perform interaction with actor
		}
	}
}
