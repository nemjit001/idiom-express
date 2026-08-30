// Copyright Tijmen Verhoef 2026


#include "Player/IdiomExpressPlayerState.h"

#include "Characters/IdiomExpressCharacter.h"
#include "Player/IdiomExpressPlayerController.h"
#include "UI/GameplayHudWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogIdiomExpressPlayerState, Log, Log);

void AIdiomExpressPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	// Get the player controller for the player state
	auto* PC = GetPlayerController();
	if (!PC)
	{
		UE_LOGF(LogIdiomExpressPlayerState, Log, "No active player controller found for %ls", *GetName());
		return;
	}
	
	// Bind to character events
	if (auto* Character = Cast<AIdiomExpressCharacter>(PC->GetCharacter()))
	{
		UE_LOGF(LogIdiomExpressPlayerState, Log, "Binding handlers to character ui events for %ls", *Character->GetName());
		Character->OnAimAtInteractableActor.AddDynamic(this, &AIdiomExpressPlayerState::OnShowInteractionPromptChanged);
	}
}

bool AIdiomExpressPlayerState::GetShowInteractionPrompt()
{
	return ShowInteractionPrompt;
}

void AIdiomExpressPlayerState::OnShowInteractionPromptChanged(bool Show)
{
	// Update stored value
	ShowInteractionPrompt = Show;
	
	// Update gameplay hud
	if (auto* PC = Cast<AIdiomExpressPlayerController>(GetPlayerController()))
	{
		if (UGameplayHudWidget* GameplayHud = PC->GetGameplayHud())
		{
			GameplayHud->ShowInteractionPrompt(Show);
		}
	}
}
