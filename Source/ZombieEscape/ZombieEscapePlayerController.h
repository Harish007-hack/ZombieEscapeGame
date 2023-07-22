// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZombieEscapePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEESCAPE_API AZombieEscapePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AZombieEscapePlayerController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	UPROPERTY(EditDefaultsOnly,Category="Widgets")
	TSubclassOf<class UUserWidget> Overlay;
	UPROPERTY(EditDefaultsOnly,Category="Widgets")
	TSubclassOf<class UUserWidget> WinScreen;
	UPROPERTY(EditDefaultsOnly,Category="Widgets")
	TSubclassOf<class UUserWidget> LoseScreen;
	
	class UUserWidget* OverLayScreen;
	
};
