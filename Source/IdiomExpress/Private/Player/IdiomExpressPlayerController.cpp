// Copyright Tijmen Verhoef 2026


#include "Player/IdiomExpressPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

DEFINE_LOG_CATEGORY_STATIC(LogIdiomExpressPlayerController, Log, Log);

void AIdiomExpressPlayerController::BeginPlay()
{
	if (GameplayInputMapping.IsNull())
	{
		UE_LOG(LogIdiomExpressPlayerController, Error, TEXT("GameplayInputMapping must not be null!"));
		return;
	}
	
	if (auto* LocalPlayer = GetLocalPlayer())
	{
		if (auto* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->AddMappingContext(GameplayInputMapping.LoadSynchronous(), 0);
		}
	}
}
