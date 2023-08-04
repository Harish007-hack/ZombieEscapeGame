// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceLastKnownLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

UBTServiceLastKnownLocationIfSeen::UBTServiceLastKnownLocationIfSeen()
{
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTServiceLastKnownLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

    if(PlayerPawn == nullptr) return;

    if(OwnerComp.GetAIOwner() == nullptr) return;

    if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn)){
        
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),PlayerPawn->GetActorLocation());
    }else{
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}
