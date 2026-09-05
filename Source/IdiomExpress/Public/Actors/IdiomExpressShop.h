// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "Actors/IdiomExpressInteractableActor.h"
#include "IdiomExpressShop.generated.h"

USTRUCT(BlueprintType)
struct FIdiomExpressShopEntry : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(Category = "Shop", BlueprintReadWrite, EditAnywhere)
	FText Word;
	UPROPERTY(Category = "Shop", BlueprintReadWrite, EditAnywhere)
	int64 Price;
};

/**
 * Interactable shop actor for Idiom Express.
 */
UCLASS()
class IDIOMEXPRESS_API AIdiomExpressShop : public AIdiomExpressInteractableActor
{
	GENERATED_BODY()
	
public:
	virtual void OnInteraction(class AIdiomExpressCharacter* Character) override;
	
	/** Set the shop menu state to 'opened'. */
	UFUNCTION(BlueprintCallable, Category = "Shop")
	virtual void OpenShopMenu();
	
	/** Set the shop menu state to 'closed'. */
	UFUNCTION(BlueprintCallable, Category = "Shop")
	virtual void CloseShopMenu();
	
protected:
	UPROPERTY(Category = "Shop", BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class UIdiomExpressGameplayMenu> ShopWidgetClass = nullptr;
	
private:
	UPROPERTY(Transient)
	bool IsShopMenuOpen = false;
	UPROPERTY(Transient)
	TObjectPtr<class AIdiomExpressPlayerController> OwningPlayer = nullptr;
	UPROPERTY(Transient)
	TObjectPtr<class UIdiomExpressGameplayMenu> ShopWidgetInstance = nullptr;
};
