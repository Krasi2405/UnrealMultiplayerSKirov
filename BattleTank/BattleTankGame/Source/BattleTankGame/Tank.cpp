// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));

	
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::Fire() 
{
	if (!Barrel) return;

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
		PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s couldn't bind firing!"), *GetName());
	}
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}


