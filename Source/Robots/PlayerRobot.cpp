// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerRobot.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Weapon.h"
#include "DebugWeapon.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
APlayerRobot::APlayerRobot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	PlayerCameraComponent->SetupAttachment(GetCapsuleComponent());
	PlayerCameraComponent->RelativeLocation = GetPawnViewLocation(); // Position the camera
	PlayerCameraComponent->bUsePawnControlRotation = true;

	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->SetupAttachment(PlayerCameraComponent);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	FirstPersonMesh->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	GetMesh()->SetOwnerNoSee(true);
}


// Called when the game starts or when spawned
void APlayerRobot::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const World = GetWorld();

	if (World && DefaultWeaponClass)
	{

		Weapon = World->SpawnActor<AWeapon>(DefaultWeaponClass, FVector(0,0,0), FRotator::ZeroRotator);
		//UE_LOG(LogTemp, Warning, TEXT(Weapon));
		Weapon->SetOwner(this);
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Grip_point"));
	}
	
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
		Cast<AWeapon>(Weapon)->BeginFireing();
	}
}

void APlayerRobot::EndFireing()
{
	if (Weapon)
	{
		Cast<AWeapon>(Weapon)->EndFireing();
	}
}

AWeapon* APlayerRobot::GetWeapon()
{
	return Weapon;
}


