// Copyright Tijmen Verhoef 2026


#include "Player/IdiomExpressPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Game/IdiomExpressGameState.h"
#include "Player/IdiomExpressPlayerState.h"
#include "UI/GameplayHudWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogIdiomExpressPlayerController, Log, Log);

void AIdiomExpressPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// Validate input mapping contexts
	if (GameplayInputMapping.IsNull())
	{
		UE_LOG(LogIdiomExpressPlayerController, Error, TEXT("GameplayInputMapping must not be null!"));
		return;
	}
	
	// Add input mapping contexts
	if (auto* LocalPlayer = GetLocalPlayer())
	{
		if (auto* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			UE_LOG(LogIdiomExpressPlayerController, Log, TEXT("Enabled GameplayInputMapping context"));
			InputSystem->AddMappingContext(GameplayInputMapping.LoadSynchronous(), 0);
		}
	}
	
	// Create gameplay HUD
	TryCreateHud();
}

void AIdiomExpressPlayerController::TryCreateHud()
{
	// Only create hud once
	if (GameplayHudInstance) {
		return;
	}
	
	// Validate hud class
	if (!IsValid(GameplayHudClass))
	{
		UE_LOG(LogIdiomExpressPlayerController, Error, TEXT("GameplayHudClass must not be null!"));
		return;
	}
	
	// Get the owning world
	UWorld* World = GetWorld();
	check(World);
	
	// Get the player state and game state for populating UI
	auto* PS = GetPlayerState<AIdiomExpressPlayerState>();
	if (!PS) {
		return;
	}
	
	auto* GS = World->GetGameState<AIdiomExpressGameState>();
	if (!GS) {
		return;
	}
	
	// Create HUD widget instance
	UE_LOGF(LogIdiomExpressPlayerController, Log, "Creating GameplayHudClass for player controller %ls", *GetName());
	GameplayHudInstance = CreateWidget<UGameplayHudWidget>(this, GameplayHudClass);
	GameplayHudInstance->AddToViewport();
	
	// Set initial gameplay HUD state
	GameplayHudInstance->ShowInteractionPrompt(PS->GetShowInteractionPrompt());
	GameplayHudInstance->SetHeldCurrencyAmount(GS->GetHeldCurrencyAmount());
}
