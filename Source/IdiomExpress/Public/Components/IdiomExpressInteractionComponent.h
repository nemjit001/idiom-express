// Copyright Tijmen Verhoef 2026

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IdiomExpressInteractionComponent.generated.h"

/**
 * Component for player-world interaction in Idiom Express.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IDIOMEXPRESS_API UIdiomExpressInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UIdiomExpressInteractionComponent();
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "Character|Components|Interaction")
	virtual void SetIsInteractingValue(bool Value);
	
	UFUNCTION(BlueprintCallable, Category = "Character|Components|Interaction")
	virtual bool ConsumeIsInteractingValue();
	
protected:
	UPROPERTY(Transient)
	bool ControlIsInteractingValue = false;
	UPROPERTY(Transient)
	bool LastIsInteractingValue = false;
};
