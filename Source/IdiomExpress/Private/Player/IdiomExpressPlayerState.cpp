// Copyright Tijmen Verhoef 2026


#include "Player/IdiomExpressPlayerState.h"

#include "Game/IdiomExpressGameState.h"
#include "Player/IdiomExpressPlayerController.h"
#include "UI/IdiomExpressGameplayHud.h"

DEFINE_LOG_CATEGORY_STATIC(LogIdiomExpressPlayerState, Log, Log);

void AIdiomExpressPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	// Get owning world for the player state
	UWorld const* World = GetWorld();
	check(World);
	
	// Get the player controller for the player state
	auto* PC = Cast<AIdiomExpressPlayerController>(GetPlayerController());
	if (!PC)
	{
		UE_LOGF(LogIdiomExpressPlayerState, Log, "No active player controller found for %ls", *GetName());
		return;
	}
	
	// Get the game state for the owning world
	auto* GS = World->GetGameState<AIdiomExpressGameState>();
	if (!GS)
	{
		UE_LOGF(LogIdiomExpressPlayerState, Log, "No active game state found for world %ls", *World->GetName());
		return;
	}
	
	// Bind to player controller events
	PC->OnShowInteractionPromptChanged.AddDynamic(this, &AIdiomExpressPlayerState::OnShowInteractionPromptChanged);
	
	// Bind to game state events
	GS->OnHeldCurrencyAmountChanged.AddDynamic(this, &AIdiomExpressPlayerState::OnHeldCurrencyAmountChanged);
	GS->OnDebtAmountChanged.AddDynamic(this, &AIdiomExpressPlayerState::OnDebtAmountChanged);
}

bool AIdiomExpressPlayerState::GetShowInteractionPrompt() const
{
	return ShowInteractionPrompt;
}

int64 AIdiomExpressPlayerState::GetHeldCurrencyAmount() const
{
	// Get owning world
	UWorld const* World = GetWorld();
	check(World);
	
	// Get game state
	if (auto const* GS = World->GetGameState<AIdiomExpressGameState>()) {
		return GS->GetHeldCurrencyAmount();
	}
	
	return 0;
}

void AIdiomExpressPlayerState::OnShowInteractionPromptChanged(bool Show)
{
	// Update stored value
	ShowInteractionPrompt = Show;
	
	// Update gameplay hud
	if (auto* PC = Cast<AIdiomExpressPlayerController>(GetPlayerController()))
	{
		if (UIdiomExpressGameplayHud* GameplayHud = PC->GetGameplayHud())
		{
			GameplayHud->ShowInteractionPrompt(Show);
		}
	}
}

void AIdiomExpressPlayerState::OnHeldCurrencyAmountChanged(int64 Value)
{
	// Update gameplay hud
	if (auto const* PC = Cast<AIdiomExpressPlayerController>(GetPlayerController()))
	{
		if (UIdiomExpressGameplayHud* GameplayHud = PC->GetGameplayHud())
		{
			GameplayHud->SetHeldCurrencyAmount(Value);
		}
	}
}

void AIdiomExpressPlayerState::OnDebtAmountChanged(int64 Value)
{
	// Update gameplay hud
	if (auto const* PC = Cast<AIdiomExpressPlayerController>(GetPlayerController()))
	{
		if (UIdiomExpressGameplayHud* GameplayHud = PC->GetGameplayHud())
		{
			GameplayHud->SetDebtAmount(Value);
		}
	}
}
