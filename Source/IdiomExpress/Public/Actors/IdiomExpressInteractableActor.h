// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IdiomExpressInteractableActor.generated.h"

/** Collision channel for world-space actor interactions. */
#define ACTOR_INTERACTION_COLLISION_CHANNEL ECollisionChannel::ECC_GameTraceChannel1

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
	/** Handle an actor entering the interaction region of the actor. */
	UFUNCTION(BlueprintCallable, Category = "Actor|Interaction")
	virtual void OnEnterInteractionRegion(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/** Handle an actor leaving the interaction region of the actor. */
	UFUNCTION(BlueprintCallable, Category = "Actor|Interaction")
	virtual void OnLeaveInteractionRegion(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable, Category = "Actor|Interaction")
	virtual void OnInteraction(class AIdiomExpressCharacter* Character);
	
	/** Handle the interaction event for this interactable object. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Actor|Interaction")
	void OnInteractionEvent(class AIdiomExpressCharacter* Character);
	
protected:	
	UPROPERTY(Category = "Actor", BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class USphereComponent> ActorCollision;
	UPROPERTY(Category = "Actor", BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class USkeletalMeshComponent> ActorMesh;
	UPROPERTY(Category = "Actor", BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class USphereComponent> InteractionRegion;
};
