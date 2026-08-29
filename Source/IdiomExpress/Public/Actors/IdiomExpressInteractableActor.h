// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IdiomExpressInteractableActor.generated.h"

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
	
protected:
	UPROPERTY(Category = "Actor", BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class USphereComponent> InteractionRegion;
	UPROPERTY(Category = "Actor", BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class USkeletalMeshComponent> ActorMesh;
};
