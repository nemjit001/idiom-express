// Copyright Tijmen Verhoef 2026


#include "Actors/IdiomExpressShop.h"

#include "Blueprint/UserWidget.h"
#include "Characters/IdiomExpressCharacter.h"
#include "Player/IdiomExpressPlayerController.h"
#include "UI/IdiomExpressGameplayMenu.h"

void AIdiomExpressShop::OnInteraction(AIdiomExpressCharacter* Character)
{
	// Handle interact only once until closed
	if (IsShopMenuOpen) {
		return;
	}
	
	// Do interaction
	Super::OnInteraction(Character);
	if (auto* PC = Cast<AIdiomExpressPlayerController>(Character->GetController()))
	{
		// Set owning player
		OwningPlayer = PC;
		
		// Open shop menu
		OpenShopMenu();
	}
}

void AIdiomExpressShop::OpenShopMenu()
{
	// Create widget
	ShopWidgetInstance = CreateWidget<UIdiomExpressGameplayMenu>(OwningPlayer, ShopWidgetClass);
	if (!IsValid(ShopWidgetInstance)) {
		return;
	}
	
	// Add widget to viewport and set focus
	ShopWidgetInstance->AddToViewport();
	ShopWidgetInstance->SetFocus();
	
	// Bind to exit event
	ShopWidgetInstance->OnExitMenu.AddUniqueDynamic(this, &AIdiomExpressShop::CloseShopMenu);

	// Set open state and enable ui input
	OwningPlayer->EnableUIInput();
	IsShopMenuOpen = true;
}

void AIdiomExpressShop::CloseShopMenu()
{
	// Unbind from exit event
	ShopWidgetInstance->OnExitMenu.RemoveDynamic(this, &AIdiomExpressShop::CloseShopMenu);
	
	// Remove widget
	ShopWidgetInstance->RemoveFromParent();
	
	// Set close state and enable game input
	OwningPlayer->EnableGameInput();
	IsShopMenuOpen = false;
	OwningPlayer = nullptr;
}
