// Copyright Tijmen Verhoef 2026


#include "Components/IdiomExpressInteractionComponent.h"

UIdiomExpressInteractionComponent::UIdiomExpressInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UIdiomExpressInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UIdiomExpressInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UIdiomExpressInteractionComponent::SetIsInteractingValue(bool Value)
{
	ControlIsInteractingValue = Value;
}

bool UIdiomExpressInteractionComponent::ConsumeIsInteractingValue()
{
	LastIsInteractingValue = ControlIsInteractingValue;
	ControlIsInteractingValue = false;
	return LastIsInteractingValue;
}

