// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IdiomExpressCharacter.generated.h"

class UCameraComponent;
class AIdiomExpressInteractableActor;
class UIdiomExpressInteractionComponent;

/**
 * Base Character class for Idiom Express.
 */
UCLASS()
class IDIOMEXPRESS_API AIdiomExpressCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AIdiomExpressCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;
	
	/** Handle player interaction input. */
	UFUNCTION(BlueprintCallable, Category = "Character|Interaction")
	virtual void Interact();
	
	/** Handle the entering of an interactable region. */
	UFUNCTION(BlueprintCallable, Category = "Character|Interaction")
	virtual void OnEnterInteractionRegion(AIdiomExpressInteractableActor* InteractableActor);
	
	/** Handle the leaving of an interactable region. */
	UFUNCTION(BlueprintCallable, Category = "Character|Interaction")
	virtual void OnLeaveInteractionRegion(AIdiomExpressInteractableActor* InteractableActor);
	
	/** Get the interaction component for the character. */
	UFUNCTION(BlueprintCallable, Category = "Character|Interaction")
	virtual UIdiomExpressInteractionComponent* GetInteractionComponent() const;

protected:
	/** Do the player aim test line trace, triggering UI updates on hit. */
	virtual void DoAimTestLineTrace();
	
	/** Do the player interaction line trace, triggering an interaction on hit. */
	virtual void DoInteractionLineTrace();
	
protected:
	// Scene components
	UPROPERTY(Category = "Character", BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UCameraComponent> PlayerCamera;
	
	// Actor components
	UPROPERTY(Category = "Character", BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UIdiomExpressInteractionComponent> InteractionComponent;
};

inline UIdiomExpressInteractionComponent* AIdiomExpressCharacter::GetInteractionComponent() const
{
	return InteractionComponent;
}
