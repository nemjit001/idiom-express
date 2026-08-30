// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IdiomExpressPlayerController.generated.h"

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
	
	/**
	 * Get the gameplay hud instance.
	 * @return
	 */
	UFUNCTION(BlueprintPure, Category = "Player|UI")
	virtual class UUserWidget* GetGameplayHud() const { return GameplayHudInstance; }
	
protected:
	UPROPERTY(Category = "Player|Input", BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<class UInputMappingContext> GameplayInputMapping;
	
	UPROPERTY(Category = "Player|UI", BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class UUserWidget> GameplayHudClass;
	
private:
	UPROPERTY(Transient)
	TObjectPtr<class UUserWidget> GameplayHudInstance;
};
