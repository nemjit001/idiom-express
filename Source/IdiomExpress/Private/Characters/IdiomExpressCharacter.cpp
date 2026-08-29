// Copyright Tijmen Verhoef 2026


#include "Characters/IdiomExpressCharacter.h"

AIdiomExpressCharacter::AIdiomExpressCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AIdiomExpressCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AIdiomExpressCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIdiomExpressCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AIdiomExpressCharacter::Interact()
{
	//
}

void AIdiomExpressCharacter::OnEnterInteractionRegion(AIdiomExpressInteractableActor* InteractableActor)
{
	//
}
	
void AIdiomExpressCharacter::OnLeaveInteractionRegion(AIdiomExpressInteractableActor* InteractableActor)
{
	//
}

