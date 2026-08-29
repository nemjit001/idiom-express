// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IdiomExpressPlayerController.generated.h"

/**
 * Player Controller for Idiom Express player characters
 */
UCLASS()
class IDIOMEXPRESS_API AIdiomExpressPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(Category = "Player Input", BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<class UInputMappingContext> GameplayInputMapping;
};
