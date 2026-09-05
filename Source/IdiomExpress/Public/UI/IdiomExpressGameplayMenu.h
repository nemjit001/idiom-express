// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IdiomExpressGameplayMenu.generated.h"

/** Multicast delegate for handling menu exits. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitMenu);

/**
 * Base widget for the Gameplay menus of Idiom Express.
 */
UCLASS()
class IDIOMEXPRESS_API UIdiomExpressGameplayMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Category = "Menu", BlueprintCallable, BlueprintAssignable)
	FOnExitMenu OnExitMenu;
};
