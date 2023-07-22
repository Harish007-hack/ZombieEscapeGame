// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_ZombieEscapeGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"
#include "ZombieEscapePlayerController.h"


ABP_ZombieEscapeGameMode::ABP_ZombieEscapeGameMode()
{
    
}

void ABP_ZombieEscapeGameMode::BeginPlay()
{
    Super::BeginPlay();

    PlayerPawn = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(this,0));

    ZombiePlayerController = Cast<AZombieEscapePlayerController>(UGameplayStatics::GetPlayerController(this,0));
}

void ABP_ZombieEscapeGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ABP_ZombieEscapeGameMode::HasActorsDied(APawn* ActorPawn)
{
    if (ActorPawn != nullptr){

        if(ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(ActorPawn)){
            ZombiePlayerController = Cast<AZombieEscapePlayerController>(PlayerCharacter->GetController());
            if (ZombiePlayerController == nullptr) return;
            ZombiePlayerController->GameHasEnded(ActorPawn,false);
        }
    }
}

