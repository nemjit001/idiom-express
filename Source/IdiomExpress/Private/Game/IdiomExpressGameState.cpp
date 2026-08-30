// Copyright Tijmen Verhoef 2026


#include "Game/IdiomExpressGameState.h"

void AIdiomExpressGameState::SetHeldCurrencyAmount(int64 Amount)
{
	CurrentHeldCurrencyAmount = Amount;
	if (OnHeldCurrencyAmountChanged.IsBound()) {
		OnHeldCurrencyAmountChanged.Broadcast(Amount);
	}
}
