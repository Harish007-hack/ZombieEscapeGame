// Fill out your copyright notice in the Description page of Project Settings.


#include "LauncherGun.h"
#include "Projectile.h"


ALauncherGun::ALauncherGun()
{
    ProjectileLaunch = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Launch"));
    ProjectileLaunch->SetupAttachment(Mesh);
}

void ALauncherGun::GunWeaponStash()
{
    Super::GunWeaponStash();

    FVector Location = ProjectileLaunch->GetComponentLocation();
    FRotator Rotation = ProjectileLaunch->GetComponentRotation();
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,Location,Rotation);
    Projectile->SetOwner(this);
}
