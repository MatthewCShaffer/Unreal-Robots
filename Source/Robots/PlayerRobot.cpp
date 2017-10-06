// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerRobot.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Weapon.h"
#include "DebugWeapon.h"


// Sets default values
APlayerRobot::APlayerRobot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	PlayerCameraComponent->SetupAttachment(GetCapsuleComponent());
	PlayerCameraComponent->RelativeLocation = GetPawnViewLocation(); // Position the camera
	PlayerCameraComponent->bUsePawnControlRotation = true;

	UWorld* const World = GetWorld();
	if (World != NULL)
		Weapon = World->SpawnActor<ADebugWeapon>();
}

// Called when the game starts or when spawned
void APlayerRobot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerRobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerRobot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerRobot::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerRobot::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerRobot::BeginFireing);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerRobot::EndFireing);

}

void APlayerRobot::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerRobot::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APlayerRobot::BeginFireing()
{
	if (Weapon)
	{
		Weapon->BeginFireing();
	}
}

void APlayerRobot::EndFireing()
{
	if (Weapon)
	{
		Weapon->EndFireing();
	}
}

AWeapon* APlayerRobot::GetWeapon()
{
	return Weapon;
}


