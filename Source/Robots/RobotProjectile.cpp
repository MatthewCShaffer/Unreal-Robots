// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ARobotProjectile::ARobotProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// Set the sphere's collision radius.
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// Set the root component to be the collision component.
	RootComponent = CollisionComponent;






	// Use this component to drive this projectile's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0;

	InitialLifeSpan = 3.0f;

	CollisionComponent->OnComponentHit.AddDynamic(this, &ARobotProjectile::OnHit);

}

// Called when the game starts or when spawned
void ARobotProjectile::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("Ready"));
	
}

// Called every frame
void ARobotProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARobotProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("Hit A thing"));
	if (OtherComponent != nullptr && OtherComponent != HitComponent)
	{
		UE_LOG(LogTemp, Log, TEXT("Hit some other thing"));
	}
}
