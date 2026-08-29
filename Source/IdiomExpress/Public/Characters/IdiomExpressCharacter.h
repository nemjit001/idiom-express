// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IdiomExpressCharacter.generated.h"

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
	UFUNCTION(Category = "Character|Interaction", BlueprintCallable)
	virtual void Interact();
};
