// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BaseCharacter.generated.h"

UCLASS()
class ZOMBIEESCAPE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Status")
	float MaxHealth = 100;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Status")
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Status")
	float MaxStamina = 100;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Status")
	float CurrentStamina;

	UPROPERTY(EditAnywhere)
	float HealthDecrementRate = 0.25f;
	UPROPERTY(EditAnywhere)
	float StaminaDecrementRate = 0.25f;
	UPROPERTY(EditAnywhere)
	float StaminaIncrementRate = 0.25;

	bool IsRun = false;

	bool IsContinous = false;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Run(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void ShootContinous(const FInputActionValue& Value);

	UPROPERTY(BlueprintReadWrite)
	float AmmosLeft = 30;
	UPROPERTY(BlueprintReadWrite)
	float MagazinesLeft = 20;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inventory-Slots")
	int SlotNo1 = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inventory-Slots")
	int SlotNo2 = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inventory-Slots")
	int SlotNo3 = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inventory-Slots")
	int SlotNo4 = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inventory-Slots")
	int SlotNo5 = 0;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool IsDead();

	void HandleDestruction();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

private:

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere,Category="Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere,Category="Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere,Category="Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere,Category="Input")
	class UInputAction* RunAction;
	
	UPROPERTY(EditAnywhere,Category="Input")
	class UInputAction* ShootAction;
	
	UPROPERTY(EditAnywhere,Category="Input")
	class UInputAction* ShootContinousAction;
	
	UPROPERTY(EditAnywhere,Category="Input")
	class UInputAction* ReloadAction;

	UPROPERTY(EditDefaultsOnly,Category="Guns")
	TSubclassOf<class AGun> GunClass;

	UPROPERTY()
	class AGun* RifleGun;

	FTimerHandle RestartTimer;

	UFUNCTION(BlueprintCallable)
	void Reload();

	UPROPERTY(EditAnywhere)
	float RestartDelay = 2.f;

	
	

	


	


};
