// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IdiomExpressPlayerController.generated.h"

/** Event delegate for notifying listeners that the interaction prompt should be shown. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowInteractionPromptChanged, bool, Show);

/**
 * Player Controller for Idiom Express player characters.
 */
UCLASS()
class IDIOMEXPRESS_API AIdiomExpressPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
public:
	/** Attempt to create the player gameplay hud. */
	UFUNCTION(BlueprintCallable, Category = "Player|UI")
	virtual void TryCreateHud();
	
	/** Show the gameplay UI interaction prompt. */
	UFUNCTION(BlueprintCallable, Category = "Player|UI")
	virtual void ShowInteractionPrompt(bool Show);
	
	/**
	 * Get the gameplay hud instance.
	 * @return
	 */
	UFUNCTION(BlueprintPure, Category = "Player|UI")
	virtual class UIdiomExpressGameplayHudWidget* GetGameplayHud() const { return GameplayHudInstance; }
	
public:
	UPROPERTY(Category = "Player|UI", BlueprintAssignable)
	FOnShowInteractionPromptChanged OnShowInteractionPromptChanged;
	
protected:
	UPROPERTY(Category = "Player|Input", BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<class UInputMappingContext> GameplayInputMapping;
	
	UPROPERTY(Category = "Player|UI", BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class UIdiomExpressGameplayHudWidget> GameplayHudClass;
	
private:
	UPROPERTY(Transient)
	TObjectPtr<class UIdiomExpressGameplayHudWidget> GameplayHudInstance;
};
