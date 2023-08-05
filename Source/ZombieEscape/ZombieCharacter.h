// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ZombieCharacter.generated.h"

UCLASS()
class ZOMBIEESCAPE_API AZombieCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombieCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Status")
	float MaxHealth = 100;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Status")
	float CurrentHealth;

	UPROPERTY(EditAnywhere,BlueprintReadWrite);
	bool IsDead = false;


	UPROPERTY(EditAnywhere)
	float HealthDecrementRate = 0.25f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

private:
	UPROPERTY(EditDefaultsOnly,Category="Input")
	class UInputMappingContext* MappingContext;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	class UInputAction* LookAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

};
