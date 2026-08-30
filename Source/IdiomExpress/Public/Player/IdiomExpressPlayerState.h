// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "IdiomExpressPlayerState.generated.h"

/**
 * Base Player State for Idiom Express. 
 */
UCLASS()
class IDIOMEXPRESS_API AIdiomExpressPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
public:
	/** Get the value that indicates if the interaction prompt should be shown. */
	UFUNCTION(BlueprintCallable, Category = "PlayerState|UI")
	virtual bool GetShowInteractionPrompt();
	
	/** Handle a change in the interaction prompt. */
	UFUNCTION(BlueprintCallable, Category = "PlayerState|UI")
	virtual void OnShowInteractionPromptChanged(bool Show);
	
private:
	UPROPERTY(Transient)
	bool ShowInteractionPrompt = false;
};
