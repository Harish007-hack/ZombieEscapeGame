// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEESCAPE_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

public:
	AZombieAIController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	class UBehaviorTree* ZombieBehaviorTree;
	
};
