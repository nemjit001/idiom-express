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
	
public:
	UFUNCTION(BlueprintCallable, Category = "Actor|Interaction")
	virtual void OnEnterInteractionRegion(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable, Category = "Actor|Interaction")
	virtual void OnLeaveInteractionRegion(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
	
protected:
	UPROPERTY(Category = "Actor", BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class USphereComponent> InteractionRegion;
	UPROPERTY(Category = "Actor", BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class USkeletalMeshComponent> ActorMesh;
};
