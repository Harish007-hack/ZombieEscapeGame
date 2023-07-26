// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class ZOMBIEESCAPE_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void GunWeaponStash();

private:
	UPROPERTY(EditAnywhere)
	USceneComponent* RootScene;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

	
	UPROPERTY(EditAnywhere,Category="Weapon Settings")
	float EndMeters = 1000.f;

	bool GunTrace(FHitResult& HitResult, FVector& ShotDirection) const;

	AController* GetOwnerController() const;

	UPROPERTY(EditDefaultsOnly,Category="ParticleEffects")
	class UParticleSystem* MuzzleFlashParticle;
	UPROPERTY(EditDefaultsOnly,Category="ParticleEffects")
	class UParticleSystem* HitFlashParticle;

	UPROPERTY(EditAnywhere,Category="Weapon Settings")
	float Damage = 10.f;

};
