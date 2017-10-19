// Fill out your copyright notice in the Description page of Project Settings.

#include "DebugWeapon.h"
#include "RobotProjectile.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ADebugWeapon::ADebugWeapon()
	: Super()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	refireTime = 0.2f;

	reloadTime = 1.0f;

	clipSize = 15;

	maxExtraAmmo = 89;

	fireCost = 2;
}

//Define Debug weapon as an instand fire weapon (Beginfire = start pew pew)
void ADebugWeapon::BeginFireing()
{
	AWeapon::BeginFireing();
	Fire();
}

void ADebugWeapon::doFire()
{
	UWorld* const World = GetWorld();

	if (World && ProjectileClass)
	{
		if (GunMesh->GetSocketByName(TEXT("Muzzle")))
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			World->SpawnActor<ARobotProjectile>(ProjectileClass, GunMesh->GetSocketLocation(TEXT("Muzzle")), ((APawn*)GetOwner())->GetBaseAimRotation(), SpawnParams)->SetOwner(this);
		}
	}
}


