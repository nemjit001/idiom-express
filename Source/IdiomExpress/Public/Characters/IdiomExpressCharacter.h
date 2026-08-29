// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IdiomExpressCharacter.generated.h"

class AIdiomExpressInteractableActor;

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
	
	/** This blueprint function implements Character-World interaction functionality. */
	UFUNCTION(BlueprintCallable, Category = "Character|Interaction")
	virtual void Interact();
	
	/** Handle the entering of an interactable region. */
	UFUNCTION(BlueprintCallable, Category = "Character|Interaction")
	virtual void OnEnterInteractionRegion(AIdiomExpressInteractableActor* InteractableActor);
	
	/** Handle the leaving of an interactable region. */
	UFUNCTION(BlueprintCallable, Category = "Character|Interaction")
	virtual void OnLeaveInteractionRegion(AIdiomExpressInteractableActor* InteractableActor);
};
