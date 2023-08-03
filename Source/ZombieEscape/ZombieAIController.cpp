// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseCharacter.h"


AZombieAIController::AZombieAIController()
{
    
}

void AZombieAIController::BeginPlay()
{
    RunBehaviorTree(ZombieBehaviorTree);

    // GetBlackboardComponent()->SetValueAsObject(TEXT("PlayerCharacter"),)
    GetBlackboardComponent()->SetValueAsFloat(TEXT("JustTrail"),17.f);
}

void AZombieAIController::Tick(float DeltaTime)
{
    
}
