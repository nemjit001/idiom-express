// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IdiomExpressPlayerController.generated.h"

/** Event delegate for notifying listeners that the interaction prompt should be shown. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowInteractionPromptChanged, bool, Show);

/**
 * Enumeration of input mapping priorities.
 */
UENUM(Blueprintable)
enum EInputMappingPriority : uint8
{
	EInputMappingPriority_GameplayInputMapping 	= 0,
};

/**
 * Enumeration of gameplay overlay menus.
 */
UENUM(Blueprintable)
enum EGameplayMenu : uint8
{
	EGameplayMenu_None					= 0,
	EGameplayMenu_BuyIdiomMenu			= 1,
	EGameplayMenu_SellIdiomMenu			= 2,
	EGameplayMenu_ConstructIdiomMenu	= 3,
};

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
	UFUNCTION(BlueprintCallable, Category = "PlayerController|UI")
	virtual void TryCreateHud();
	
	/** Show the gameplay UI interaction prompt. */
	UFUNCTION(BlueprintCallable, Category = "PlayerController|UI")
	virtual void ShowInteractionPrompt(bool Show);
	
	UFUNCTION(BlueprintCallable, Category = "PlayerController|UI")
	virtual void EnableGameInput();
	
	UFUNCTION(BlueprintCallable, Category = "PlayerController|UI")
	virtual void EnableUIInput();	
	
	/**
	 * Get the gameplay hud instance.
	 * @return
	 */
	UFUNCTION(BlueprintCallable, Category = "PlayerController|UI")
	virtual class UIdiomExpressGameplayHud* GetGameplayHud() const { return GameplayHudInstance; }
	
protected:
	/** Enable an input mapping context with a priority. */
	virtual void EnableInputMappingContext(TSoftObjectPtr<class UInputMappingContext> InputMappingContext, EInputMappingPriority priority);
	
	/** Remove an enabled mapping context. */
	virtual void DisableInputMappingContext(TSoftObjectPtr<class UInputMappingContext> InputMappingContext);
	
public:
	UPROPERTY(Category = "PlayerController|UI", BlueprintAssignable)
	FOnShowInteractionPromptChanged OnShowInteractionPromptChanged;
	
protected:
	UPROPERTY(Category = "PlayerController|UI", BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<class UInputMappingContext> GameplayInputMapping;
	UPROPERTY(Category = "PlayerController|UI", BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class UIdiomExpressGameplayHud> GameplayHudClass;
	
private:
	UPROPERTY(Transient)
	TObjectPtr<class UIdiomExpressGameplayHud> GameplayHudInstance;
};
