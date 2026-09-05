// Copyright Tijmen Verhoef 2026


#include "Player/IdiomExpressPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Game/IdiomExpressGameState.h"
#include "Player/IdiomExpressPlayerState.h"
#include "UI/IdiomExpressGameplayHud.h"

DEFINE_LOG_CATEGORY_STATIC(LogIdiomExpressPlayerController, Log, Log);

void AIdiomExpressPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// Enable default input mapping context
	EnableInputMappingContext(GameplayInputMapping, EInputMappingPriority_GameplayInputMapping);
	
	// Create gameplay HUD
	TryCreateHud();
	
	// Enable game input
	EnableGameInput();
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
	UWorld const* World = GetWorld();
	check(World);
	
	// Get the player state and game state for populating UI
	auto const* PS = GetPlayerState<AIdiomExpressPlayerState>();
	if (!PS) {
		return;
	}
	
	auto const* GS = World->GetGameState<AIdiomExpressGameState>();
	if (!GS) {
		return;
	}
	
	// Create HUD widget instance
	UE_LOGF(LogIdiomExpressPlayerController, Log, "Creating GameplayHudClass for player controller %ls", *GetName());
	GameplayHudInstance = CreateWidget<UIdiomExpressGameplayHud>(this, GameplayHudClass);
	GameplayHudInstance->AddToViewport();
	
	// Set initial gameplay HUD state
	GameplayHudInstance->ShowInteractionPrompt(PS->GetShowInteractionPrompt());
	GameplayHudInstance->SetHeldCurrencyAmount(GS->GetHeldCurrencyAmount());
	GameplayHudInstance->SetDebtAmount(GS->GetDebtAmount());
}

void AIdiomExpressPlayerController::ShowInteractionPrompt(bool Show)
{
	// Broadcast show event for interaction prompt
	if (OnShowInteractionPromptChanged.IsBound()) {
		OnShowInteractionPromptChanged.Broadcast(Show);
	}
}

void AIdiomExpressPlayerController::EnableGameInput()
{
	// Set input mode to game only
	FInputModeGameOnly GameOnlyMode{};
	GameOnlyMode.SetConsumeCaptureMouseDown(true);
	SetInputMode(GameOnlyMode);
	
	// Hide mouse cursor
	SetShowMouseCursor(false);
}

void AIdiomExpressPlayerController::EnableUIInput()
{
	// Set input mode to ui only
	FInputModeUIOnly UIOnlyMode{};
	UIOnlyMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
	SetInputMode(UIOnlyMode);
	
	// Show mouse cursor
	SetShowMouseCursor(true);
}

void AIdiomExpressPlayerController::EnableInputMappingContext(TSoftObjectPtr<UInputMappingContext> InputMappingContext, EInputMappingPriority priority)
{
	// Validate input mapping context
	if (InputMappingContext.IsNull())
	{
		UE_LOG(LogIdiomExpressPlayerController, Error, TEXT("Input mapping context must not be null!"));
		return;
	}
	
	// Add input mapping context
	if (auto* LocalPlayer = GetLocalPlayer())
	{
		if (auto* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			UE_LOG(LogIdiomExpressPlayerController, Log, TEXT("Enabled input mapping context"));
			InputSystem->AddMappingContext(InputMappingContext.LoadSynchronous(), priority);
		}
	}
}

void AIdiomExpressPlayerController::DisableInputMappingContext(TSoftObjectPtr<UInputMappingContext> InputMappingContext)
{
	// Validate input mapping context
	if (InputMappingContext.IsNull())
	{
		UE_LOG(LogIdiomExpressPlayerController, Error, TEXT("Input mapping context must not be null!"));
		return;
	}
	
	// Remove input mapping context
	if (auto* LocalPlayer = GetLocalPlayer())
	{
		if (auto* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			UE_LOG(LogIdiomExpressPlayerController, Log, TEXT("Disabled context"));
			InputSystem->RemoveMappingContext(InputMappingContext.LoadSynchronous());
		}
	}
}
