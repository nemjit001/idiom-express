// Copyright Tijmen Verhoef 2026


#include "Player/IdiomExpressPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogIdiomExpressPlayerController, Log, Log);

void AIdiomExpressPlayerController::BeginPlay()
{	
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
	// Validate hud class
	if (!IsValid(GameplayHudClass))
	{
		UE_LOG(LogIdiomExpressPlayerController, Error, TEXT("GameplayHudClass must not be null!"));
		return;
	}
	
	// Create HUD widget instance
	GameplayHudInstance = CreateWidget(this, GameplayHudClass);
	if (GameplayHudInstance)
	{
		UE_LOGF(LogIdiomExpressPlayerController, Log, "Created GameplayHudClass for player controller %ls", *GetName());
		GameplayHudInstance->AddToViewport();
	}
}
