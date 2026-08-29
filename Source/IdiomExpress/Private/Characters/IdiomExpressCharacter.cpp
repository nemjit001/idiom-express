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
#if		UE_BUILD_DEVELOPMENT
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0F, FColor::Green, TEXT("Interact triggered"));
	}
#endif // UE_BUILD_DEVELOPMENT
}

