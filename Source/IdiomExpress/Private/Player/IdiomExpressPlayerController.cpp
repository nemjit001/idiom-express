// Copyright Tijmen Verhoef 2026


#include "Player/IdiomExpressPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void AIdiomExpressPlayerController::BeginPlay()
{
	if (GameplayInputMapping.IsNull())
	{
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
