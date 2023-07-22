// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieEscapePlayerController.h"
#include "Blueprint/UserWidget.h"


AZombieEscapePlayerController::AZombieEscapePlayerController()
{
    
}

void AZombieEscapePlayerController::BeginPlay()
{
    Super::BeginPlay();
    OverLayScreen = CreateWidget(this,Overlay);
    OverLayScreen->AddToViewport();
}

void AZombieEscapePlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus,bIsWinner);
    OverLayScreen->RemoveFromParent();
    if(bIsWinner){
        UUserWidget* WinnerScreen = CreateWidget(this,WinScreen);
        WinnerScreen->AddToViewport();
    }else{
        UUserWidget* LoserScreen = CreateWidget(this,LoseScreen);
        LoserScreen->AddToViewport();
    }
}
