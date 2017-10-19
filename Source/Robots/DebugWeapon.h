// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "DebugWeapon.generated.h"

/**
 * 
 */
UCLASS()
class ROBOTS_API ADebugWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ADebugWeapon();

	void BeginFireing() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		TSubclassOf<class ARobotProjectile> ProjectileClass;

	void doFire() override;
	
};
