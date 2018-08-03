// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet) 
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector AimLocation, float LaunchSpeed)
{
	if (Barrel)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Aiming from %s to %s"), *GetOwner()->GetName(), *Barrel->GetComponentLocation().ToString(), *AimLocation.ToString())
		
		FVector ProjectileVelocity;
		FCollisionResponseParams CollisionResponse;
		TArray<AActor*> ObjectsToIgnore;
		ObjectsToIgnore.Add(GetOwner());
		if (UGameplayStatics::SuggestProjectileVelocity(
			this,
			ProjectileVelocity,
			Barrel->GetComponentLocation(),
			AimLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		)) 
		{
			FVector AimDirection = ProjectileVelocity.GetSafeNormal();
			UE_LOG(LogTemp, Warning, TEXT("Suggested Velocity: %s"), *AimDirection.ToString());
		}
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Barrel reference not set on %s"), *GetOwner()->GetName())
	}
}