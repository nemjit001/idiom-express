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
	
};
