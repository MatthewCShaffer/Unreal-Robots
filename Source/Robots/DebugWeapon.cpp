// Fill out your copyright notice in the Description page of Project Settings.

#include "DebugWeapon.h"

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




