// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "Public/TimerManager.h"
#include "Engine/Engine.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReloading = false;
	bWaitingToRefire = false;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	if (GunMesh) {
		GunMesh->SetOwnerNoSee(true);
		RootComponent = GunMesh;
	}


	FirstPersonGunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonGunMesh"));
	if (FirstPersonGunMesh)
	{
		FirstPersonGunMesh->SetOnlyOwnerSee(true);
		FirstPersonGunMesh->SetupAttachment(GetRootComponent());
	}


}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	clipAmmo = clipSize;
	extraAmmo = maxExtraAmmo;


}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

USkeletalMeshComponent* AWeapon::GetFirstPersonGunMesh()
{
	return FirstPersonGunMesh;
}

int32 AWeapon::getTotalAmmo()
{
	return clipAmmo + extraAmmo;
}

int32 AWeapon::getClipAmmo()
{
	return clipAmmo;
}

int32 AWeapon::getExtraAmmo()
{
	return extraAmmo;
}


bool AWeapon::isClipFull()
{
	return clipAmmo == clipSize;
}

bool AWeapon::CanFire()
{
	return !isReloading() && !isWaitingToRefire() && clipAmmo >= fireCost;
}

void AWeapon::BeginFireing()
{
	bFireing = true;
	Fire();
}

void AWeapon::EndFireing()
{
	bFireing = false;
}

void AWeapon::CheckForRefire()
{
	if (bFireing)
		Fire();
}


void AWeapon::Fire()
{
	if (CanFire())
	{
		doFire();
		RemoveAmmo(fireCost, true);
		if (!isWaitingToRefire() && refireTime)
		{
			bWaitingToRefire = true;
			GetWorldTimerManager().SetTimer(refireTimer, this, &AWeapon::OnRefireReady, refireTime);
		}
	}
	else
		//If we can't fire then reload if we need to instead
		checkForceReload();
	
}

void AWeapon::doFire()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Bang!"));
	}
}

void AWeapon::OnRefireReady()
{
	GetWorldTimerManager().ClearTimer(refireTimer);
	bWaitingToRefire = false;
	CheckForRefire();
}


void AWeapon::reload()
{
	if (!isReloading() && extraAmmo > 0 && !isClipFull())
	{
		if (reloadTime)
		{
			bReloading = true;
			GetWorldTimerManager().SetTimer(reloadTimer, this, &AWeapon::OnReload, reloadTime);
		}
		else
		{
			OnReload();
		}
	}
}

void AWeapon::OnReload()
{
	GetWorldTimerManager().ClearTimer(reloadTimer);
	refillClip();
	bReloading = false;
	CheckForRefire();
}

void AWeapon::checkForceReload()
{
	if((clipAmmo == 0 || clipAmmo < fireCost) && extraAmmo)
		reload();
}

bool AWeapon::isReloading()
{
	return bReloading;
}

bool AWeapon::isWaitingToRefire()
{
	return bWaitingToRefire;
}

void AWeapon::addAmmo(int32 additionalAmmo, bool useClipAmmo)
{
	if (additionalAmmo)
	{
		if (useClipAmmo)
		{
			if (clipAmmo + additionalAmmo > clipSize)
			{
				additionalAmmo -= clipSize - clipAmmo;
				clipAmmo = clipSize;
			}
			else
				clipAmmo += additionalAmmo;
		}

		extraAmmo = FMath::Clamp(extraAmmo + additionalAmmo, 0, maxExtraAmmo);

		CheckForRefire();
	}
}

void AWeapon::RemoveAmmo(int32 removedAmmo, bool useClipAmmo)
{
	if (removedAmmo)
	{
		if (useClipAmmo)
		{
			//Take the ammo out of the clip, if its greated then the clip ammo, reduce clip to 0; set removedAmmo to remaing ammo to remove
			if (clipAmmo >= removedAmmo)
			{
				clipAmmo -= removedAmmo;
				removedAmmo = 0;
			}
			else
			{
				removedAmmo -= clipAmmo;
				clipAmmo = 0;
			}
		}

		extraAmmo = FMath::Clamp(extraAmmo - removedAmmo, 0, maxExtraAmmo);

		//checkForceReload(); Auto reload when after last show if you dont have enougth ammo, not sure if I like
	}
}

void AWeapon::refillClip()
{
	if (!isClipFull())
	{
		if (extraAmmo >= clipSize - clipAmmo)
		{
			extraAmmo -= clipSize - clipAmmo;
			clipAmmo = clipSize;
		}
		else
		{
			clipAmmo += extraAmmo;
			extraAmmo = 0;
		}
	}
}