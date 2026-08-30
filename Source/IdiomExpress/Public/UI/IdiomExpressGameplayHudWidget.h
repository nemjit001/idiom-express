// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IdiomExpressGameplayHudWidget.generated.h"

/**
 * Base widget for the Gameplay HUD of Idiom Express.
 */
UCLASS()
class IDIOMEXPRESS_API UIdiomExpressGameplayHudWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintImplementableEvent, Category = "UI|Gameplay")
	void ShowInteractionPrompt(bool Show);
	UFUNCTION(BlueprintImplementableEvent, Category = "UI|Gameplay")
	void SetHeldCurrencyAmount(int64 Value);
	UFUNCTION(BlueprintImplementableEvent, Category = "UI|Gameplay")
	void SetDebtAmount(int64 Value);
};
