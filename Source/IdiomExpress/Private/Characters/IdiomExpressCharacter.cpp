// Copyright Tijmen Verhoef 2026


#include "Characters/IdiomExpressCharacter.h"

#include "Actors/IdiomExpressInteractableActor.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/IdiomExpressInteractionComponent.h"
#include "Player/IdiomExpressPlayerController.h"

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

	// Handle player interaction input
	if (auto* Interaction = GetInteractionComponent())
	{
		// Consume interacting value
		const bool InteractOnHit = Interaction->ConsumeIsInteractingValue();
		
		// Only process interactions if in interaction region
		if (Interaction->IsInInteractionRegion())
		{
			// Send aim test line trace and trigger interaction if input is pressed
			DoInteractionLineTrace(InteractOnHit);
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

void AIdiomExpressCharacter::OnEnterInteractionRegion()
{
	// Notify interaction component of entering interaction region
	if (auto* Interaction = GetInteractionComponent()) {
		Interaction->EnterInteractionRegion();
	}
}
	
void AIdiomExpressCharacter::OnLeaveInteractionRegion()
{
	// Notify interaction component of leaving interaction region
	if (auto* Interaction = GetInteractionComponent()) {
		Interaction->LeaveInteractionRegion();
	}
	
	// Hide interaction prompt
	ShowInteractionPrompt(false);
}

void AIdiomExpressCharacter::ShowInteractionPrompt(bool Show)
{
	if (auto* PC = GetController<AIdiomExpressPlayerController>()) {
		PC->ShowInteractionPrompt(Show);
	}
}

void AIdiomExpressCharacter::DoInteractionLineTrace(bool InteractOnHit)
{
	// Get start and end points for the interaction trace
	FVector ViewOrigin{};
	FRotator ViewDirection{};
	GetActorEyesViewPoint(ViewOrigin, ViewDirection);
	FVector const TraceEndPoint = ViewOrigin + ViewDirection.Vector() * CHARACTER_INTERACTION_LINE_TRACE_LENGTH;
	
	// Get the world for the actor
	UWorld* World = GetWorld();
	check(World);
	
	// Initially hide interaction prompt
	ShowInteractionPrompt(false);
	
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
			// Show interaction prompt.
			ShowInteractionPrompt(true);
			
			// Trigger an interaction if required.
			if (InteractOnHit)
			{
				UE_LOGF(LogIdiomExpressCharacter, Log,
					"Performing interaction: %ls interacting with %ls",
					*GetName(),
					*InteractableActor->GetName()
				);
				
				// Interact with actor :)
				InteractableActor->OnInteraction(this);
			}
		}
	}
}
