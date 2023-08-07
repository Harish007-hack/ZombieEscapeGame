// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AZombieCharacter::AZombieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(50.f,96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->MaxWalkSpeed = 700.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->JumpZVelocity = 0.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 700.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 350.f;



}

// Called when the game starts or when spawned
void AZombieCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PlayerController = Cast<APlayerController>(GetController())){
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())){
			Subsystem->AddMappingContext(MappingContext,0);
		}
	}
	
	CurrentHealth = MaxHealth;
}

// Called every frame
void AZombieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZombieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)){

		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AZombieCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&AZombieCharacter::Look);
	}

}

float AZombieCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageCaused = Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);

	CurrentHealth -= DamageCaused;

	if(CurrentHealth <= 0.f){
		IsDead = true;
	}

	if(IsDead){
		HandleDestruction();
	}

	return DamageCaused;
}






void AZombieCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if(GetController() != nullptr){

		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);


		AddMovementInput(ForwardDirection,MovementVector.Y);
		AddMovementInput(RightDirection,MovementVector.X); 

	}
}

void AZombieCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookDirectionVector = Value.Get<FVector2D>();

	if(GetController() != nullptr){
		AddControllerYawInput(LookDirectionVector.X);
		AddControllerPitchInput(LookDirectionVector.Y);
	}
}



void AZombieCharacter::HandleDestruction()
{
	DetachFromControllerPendingDestroy(); //detaches pawn from controller after death.
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}