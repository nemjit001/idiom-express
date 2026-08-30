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
	
	/** Register the entering of an interaction region. */
	UFUNCTION(BlueprintCallable, Category = "Character|Components|Interaction")
	virtual void EnterInteractionRegion();
	
	/** Register the leaving of an interaction region. */
	UFUNCTION(BlueprintCallable, Category = "Character|Components|Interaction")
	virtual void LeaveInteractionRegion();
	
	/** Check if the owner pawn is in an interaction region. */
	UFUNCTION(BlueprintCallable, Category = "Character|Components|Interaction")
	virtual bool IsInInteractionRegion() const;
	
	/** Set the input value for the interaction input. */
	UFUNCTION(BlueprintCallable, Category = "Character|Components|Interaction")
	virtual void SetIsInteractingValue(bool Value);
	
	/** Consume the value for the interaction input. */
	UFUNCTION(BlueprintCallable, Category = "Character|Components|Interaction")
	virtual bool ConsumeIsInteractingValue();
	
protected:
	UPROPERTY(Transient)
	bool ControlIsInteractingValue = false;
	UPROPERTY(Transient)
	bool LastIsInteractingValue = false;
	UPROPERTY(Transient)
	int32 ActiveInteractionRegionCount = 0;
};

inline void UIdiomExpressInteractionComponent::EnterInteractionRegion()
{
	ActiveInteractionRegionCount++;
}
	
inline void UIdiomExpressInteractionComponent::LeaveInteractionRegion()
{
	ActiveInteractionRegionCount--;
}

inline bool UIdiomExpressInteractionComponent::IsInInteractionRegion() const
{
	return ActiveInteractionRegionCount > 0;
}
