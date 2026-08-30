// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "IdiomExpressGameState.generated.h"

/** Event delegate for updating the held currency amount in the game state. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeldCurrencyAmountChanged, int64, Amount);

/**
 * Default game state for Idiom Express.
 */
UCLASS()
class IDIOMEXPRESS_API AIdiomExpressGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	/** Set the held currency amount. */
	UFUNCTION(BlueprintCallable, Category = "Game|Currency")
	virtual void SetHeldCurrencyAmount(int64 Amount);
	
	/** Get the held currency amount. */
	UFUNCTION(BlueprintCallable, Category = "Game|Currency")
	virtual int64 GetHeldCurrencyAmount() const { return CurrentHeldCurrencyAmount; }
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Game|Events")
	FOnHeldCurrencyAmountChanged OnHeldCurrencyAmountChanged;
	
protected:
	UPROPERTY(Category = "Game|Currency", BlueprintReadOnly, VisibleAnywhere)
	int64 CurrentHeldCurrencyAmount = 0;
};
