// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SpotLightComponent.h"
#include "BP_ZombieEscapeGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Gun.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f,96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,500.f,0.f);

	GetCharacterMovement()->MaxWalkSpeed = 1200.f;
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm Boom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	
	

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())){
		if(UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())){
			SubSystem->AddMappingContext(InputMapping,0);
		}
	}

	CurrentHealth = MaxHealth;
	CurrentStamina = MaxStamina;
	RifleGun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
	RifleGun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("weapon_r"));
	RifleGun->SetOwner(this);
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CurrentHealth > 0.f){
		CurrentHealth = CurrentHealth - (DeltaTime*HealthDecrementRate);
	}
	// UE_LOG(LogTemp, Warning, TEXT("%f"),CurrentHealth);

	if(IsRun){
		if(CurrentStamina > 0){
			CurrentStamina = CurrentStamina - (DeltaTime*StaminaDecrementRate);
		}
	}else{
		if(CurrentStamina < 100){
			CurrentStamina = CurrentStamina + (DeltaTime*StaminaIncrementRate);
		}
	}

	// UE_LOG(LogTemp, Warning, TEXT("%f"),CurrentHealth);

	if(IsDead()){
		ABP_ZombieEscapeGameMode* ZombieGameMode =  GetWorld()->GetAuthGameMode<ABP_ZombieEscapeGameMode>();
		if(ZombieGameMode != nullptr){
			ZombieGameMode->HasActorsDied(this);
		}
		HandleDestruction();
	}

	// if(AmmosLeft == 0){
	// 	Reload();
	// 	// GetWorldTimerManager().SetTimer(RestartTimer,this,&ABaseCharacter::Reload,RestartDelay);
	// }


	UE_LOG(LogTemp, Error, TEXT("%f"),AmmosLeft);
	UE_LOG(LogTemp, Error, TEXT("%f"),MagazinesLeft);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent =  CastChecked<UEnhancedInputComponent>(PlayerInputComponent)){

		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ABaseCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ABaseCharacter::Look);

		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Triggered,this,&ACharacter::Jump);

		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Completed,this,&ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(RunAction,ETriggerEvent::Triggered,this,&ABaseCharacter::Run);

		EnhancedInputComponent->BindAction(RunAction,ETriggerEvent::Completed,this,&ABaseCharacter::Run);

		EnhancedInputComponent->BindAction(ShootContinousAction,ETriggerEvent::Started,this,&ABaseCharacter::ShootContinous);

		EnhancedInputComponent->BindAction(ShootAction,ETriggerEvent::Triggered,this,&ABaseCharacter::Shoot);

		EnhancedInputComponent->BindAction(ReloadAction,ETriggerEvent::Started,this,&ABaseCharacter::Reload);
	}

}



void ABaseCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if(GetController() != nullptr){

		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		if(!IsRun){
			MovementVector.X /=2;
			MovementVector.Y /=2;
		}

		AddMovementInput(ForwardDirection,MovementVector.Y);
		AddMovementInput(RightDirection,MovementVector.X);
	}
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAtVector = Value.Get<FVector2D>();

	if(GetController() != nullptr){
		
		AddControllerYawInput(LookAtVector.X);
		AddControllerPitchInput(LookAtVector.Y);
	}
}

void ABaseCharacter::Run(const FInputActionValue& Value)
{
	IsRun = Value.Get<bool>();
}

void ABaseCharacter::Shoot(const FInputActionValue& Value)
{
	if(AmmosLeft != 0){
		if(MagazinesLeft > 0){
			RifleGun->GunWeaponStash();	
			AmmosLeft-=1;
		}
	}

	
}

void ABaseCharacter::ShootContinous(const FInputActionValue& Value)
{
	IsContinous = !IsContinous;
	if(IsContinous){
		UE_LOG(LogTemp, Error, TEXT("Your message"));
	}
}

bool ABaseCharacter::IsDead()
{
	return CurrentHealth <= 0;
}

void ABaseCharacter::HandleDestruction()
{
	DetachFromControllerPendingDestroy(); //detaches pawn from controller after death.
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

float ABaseCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);
}

void ABaseCharacter::Reload()
{
	if(AmmosLeft == 0){
		if(MagazinesLeft >= 0){
			AmmosLeft = 30;
			MagazinesLeft-=1;
		}
	}
}
