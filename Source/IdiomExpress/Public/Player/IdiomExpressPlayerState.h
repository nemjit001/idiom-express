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
	
	/** Get the held currency amount. */
	UFUNCTION(BlueprintCallable, Category = "PlayerState|UI")
	virtual int64 GetHeldCurrencyAmount();
	
	/** Handle a change in the interaction prompt. */
	UFUNCTION(BlueprintCallable, Category = "PlayerState|UI")
	virtual void OnShowInteractionPromptChanged(bool Show);
	
	/** Handle a change in the held currency amount. */
	virtual void OnHeldCurrencyAmountChanged(int64 Value);
	
private:
	UPROPERTY(Transient)
	bool ShowInteractionPrompt = false;
};
