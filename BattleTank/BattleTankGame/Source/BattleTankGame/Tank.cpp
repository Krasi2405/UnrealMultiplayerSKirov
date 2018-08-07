// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"

#include "Projectile.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "TankTrack.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MovementComponent"));

	LastFireTime = 0.f;
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::AttemptFire()
{
	if(CanFire())
	{
		LastFireTime = GetWorld()->GetTimeSeconds();
		Fire();
	}
}

void ATank::Fire() 
{
	if (!Barrel || !ProjectileBlueprint) 
	{
		UE_LOG(LogTemp, Error, TEXT("%s attempted to fire with no barrel or projectile set!"), *GetName())
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("%s Fires!"), *GetName());
	FActorSpawnParameters SpawnInfo;
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint, 
		Barrel->GetSocketLocation("Projectile"), 
		Barrel->GetForwardVector().Rotation(), 
		SpawnInfo
	);

	Projectile->LaunchProjectile(LaunchSpeed);
}

bool ATank::CanFire()
{
	bool bCanFire = (GetWorld()->GetTimeSeconds() > LastFireTime + ReloadTime);
	return bCanFire;
}

void ATank::AimAt(FVector AimLocation)
{
	TankAimingComponent->AimAt(AimLocation, LaunchSpeed);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::AttemptFire);

		BindPlayerMovementInput(PlayerInputComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: no input component!"), *GetName());
	}
}

void ATank::BindPlayerMovementInput(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(FName("HorizontalMovement"), TankMovementComponent, &UTankMovementComponent::HorizontalMovement);
	PlayerInputComponent->BindAxis(FName("VerticalMovement"), TankMovementComponent, &UTankMovementComponent::VerticalMovement);
}


void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

