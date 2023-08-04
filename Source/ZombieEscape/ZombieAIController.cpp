// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"


AZombieAIController::AZombieAIController()
{
    
}

void AZombieAIController::BeginPlay()
{
    Super::BeginPlay();
    RunBehaviorTree(ZombieBehaviorTree);

    // GetBlackboardComponent()->SetValueAsObject(TEXT("PlayerCharacter"),)
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    APawn* AIPawn = GetPawn();
    // GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
    GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());

}

void AZombieAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
