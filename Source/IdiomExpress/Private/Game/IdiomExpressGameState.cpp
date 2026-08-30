// Copyright Tijmen Verhoef 2026


#include "Game/IdiomExpressGameState.h"

void AIdiomExpressGameState::SetHeldCurrencyAmount(int64 Amount)
{
	CurrentHeldCurrencyAmount = Amount;
	if (OnHeldCurrencyAmountChanged.IsBound()) {
		OnHeldCurrencyAmountChanged.Broadcast(Amount);
	}
}

void AIdiomExpressGameState::SetDebtAmount(int64 Amount)
{
	CurrentDebtAmount = Amount;
	if (OnDebtAmountChanged.IsBound()) {
		OnDebtAmountChanged.Broadcast(Amount);
	}
}
