// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ZombieEscapeGameMode.generated.h"

UCLASS(minimalapi)
class AZombieEscapeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AZombieEscapeGameMode();

public:
	virtual void Tick(float DeltaTime) override;

};



