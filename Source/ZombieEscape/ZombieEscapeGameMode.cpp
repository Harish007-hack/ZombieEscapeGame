// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZombieEscapeGameMode.h"
#include "ZombieEscapeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZombieEscapeGameMode::AZombieEscapeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AZombieEscapeGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
