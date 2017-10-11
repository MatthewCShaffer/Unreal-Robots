// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS(abstract)
class ROBOTS_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();


private: 
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* GunMesh;

	FTimerHandle refireTimer;

	FTimerHandle reloadTimer;


	//True when the wepon is reloading
	bool bReloading;

	//True when the weapon is waiting before it can fire again
	bool bWaitingToRefire;

	//True when fieing button is held down
	bool bFireing;

	//Ammo for weapon in addition to ammo in clip
	int32 extraAmmo;
	//The crrently loaded Ammo amount
	int32 clipAmmo;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//The maximum ammo this weapon can have in addition to clip ammo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int32 maxExtraAmmo;

	//The amount of ammo that can be fired before the weapon must reload
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int32 clipSize;

	//The ammount of ammo used during one fire of the weapon (The weapon cannot fire when there is less ammo then this)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int32 fireCost;

	//The time that it akes to reload the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fireing)
	float reloadTime;

	//The time between weapon shots
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fireing)
	float refireTime;

	void checkForceReload();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	bool isReloading();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	bool isWaitingToRefire();

	void refillClip();

	//Called when we need to tell the weapon to refire if it is fireing currently
	void CheckForRefire();

	//The fire effect of the weapon
	virtual void doFire();

	virtual void OnRefireReady();

	virtual void OnReload();

	virtual bool isClipFull();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool CanFire();

	//Calls the fire logic
	virtual void Fire();

	virtual void reload();
	
	virtual void addAmmo(int32 ammo, bool useClipAmmo);

	virtual void RemoveAmmo(int32 ammo, bool useClipAmmo);

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	virtual int32 getTotalAmmo();

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	virtual int32 getClipAmmo();

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	virtual int32 getExtraAmmo();

	virtual void BeginFireing();

	virtual void EndFireing();

};
