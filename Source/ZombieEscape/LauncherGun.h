// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "LauncherGun.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEESCAPE_API ALauncherGun : public AGun
{
	GENERATED_BODY()

public:
	ALauncherGun();

public:
	// UFUNCTION(BlueprintCallable)
	virtual void GunWeaponStash() override;

private:
	UPROPERTY(EditAnywhere)
	USceneComponent* ProjectileLaunch;

	UPROPERTY(EditDefaultsOnly,Category="Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;	
};
