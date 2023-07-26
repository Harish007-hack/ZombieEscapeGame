// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootScene);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	Mesh->SetupAttachment(RootScene);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::GunWeaponStash()
{
	AController* PawnController = GetOwnerController();
	
	FHitResult HitResult;
	FVector ShotDirection;

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlashParticle,Mesh,TEXT("MuzzleFlashSocket"));

	bool HasBeenShot = GunTrace(HitResult,ShotDirection);
	if(HasBeenShot){
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitFlashParticle,HitResult.Location,ShotDirection.Rotation());
		AActor* HitActor = HitResult.GetActor();
		if(HitActor != nullptr){
			FPointDamageEvent DamageEvent(Damage,HitResult,ShotDirection,nullptr);
			HitActor->TakeDamage(Damage,DamageEvent,PawnController,this);

		}

	}
	
	// DrawDebugLine(GetWorld(),Location,End,FColor::Red,true);
	// UE_LOG(LogTemp, Warning, TEXT("%s"),*HitResult.Location.ToCompactString());
	// if(HasHit){
	// 	
	// }

}

bool AGun::GunTrace(FHitResult& HitResult, FVector& ShotDirection) const
{
	FVector Location;
	FRotator Rotation;
	AController* PawnController = GetOwnerController();
	PawnController->GetPlayerViewPoint(Location,Rotation);
	FVector End = Location + Rotation.Vector()*EndMeters;
	ShotDirection = -Rotation.Vector();
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(HitResult,Location,End,ECollisionChannel::ECC_GameTraceChannel1,Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	return OwnerPawn->GetController();
}





