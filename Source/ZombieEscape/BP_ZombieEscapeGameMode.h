// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BP_ZombieEscapeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEESCAPE_API ABP_ZombieEscapeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABP_ZombieEscapeGameMode();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void HasActorsDied(APawn* ActorPawn);

private:
	class ABaseCharacter* PlayerPawn;
	class AZombieEscapePlayerController* ZombiePlayerController;

	

	
};
