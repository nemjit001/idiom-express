// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IdiomExpressInteractableActor.generated.h"

/** Collision channel for world-space actor interactions. */
#define ACTOR_INTERACTION_COLLISION_CHANNEL ECollisionChannel::ECC_GameTraceChannel1

/** Delegate for receiving interaction events on the actor. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorInteractionReceived);

/** Delegate for receiving aim events on the actor. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorAimedAt);

/**
 * Base Interactable Actor class for Idiom Express.
 */
UCLASS()
class IDIOMEXPRESS_API AIdiomExpressInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AIdiomExpressInteractableActor();

protected:
	virtual void BeginPlay() override;
	
public:
	/** Do the interaction with this interactable actor. */
	UFUNCTION(BlueprintCallable, Category = "Actor|Interaction")
	virtual void DoInteraction();
	
	/** Notify this actor that it is being aimed at. */
	virtual void NotifyIsAimedAt();
	
	/** Handle an actor entering the interaction region of the actor. */
	UFUNCTION(BlueprintCallable, Category = "Actor|Interaction")
	virtual void OnEnterInteractionRegion(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/** Handle an actor leaving the interaction region of the actor. */
	UFUNCTION(BlueprintCallable, Category = "Actor|Interaction")
	virtual void OnLeaveInteractionRegion(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

public:
	/** Delegate for notifying subscribers that this actor received an interaction event. */
	UPROPERTY(Category = "Actor|Interaction", BlueprintAssignable, VisibleAnywhere);
	FOnActorInteractionReceived OnActorInteractionReceived;
	/** Delegate for notifying subscribers that this actor is being aimed at. */
	UPROPERTY(Category = "Actor|Interaction", BlueprintAssignable, VisibleAnywhere);
	FOnActorAimedAt OnActorAimedAt;
	
protected:
	UPROPERTY(Category = "Actor", BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class USphereComponent> InteractionRegion;
	UPROPERTY(Category = "Actor", BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class USkeletalMeshComponent> ActorMesh;
};
