// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankMovementComponent;
class UTankTrack;
class AProjectile;

UCLASS()
class BATTLETANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector AimLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	void AttemptFire();
	

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent;


private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 17000.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	float LastFireTime;

	bool CanFire();

	void Fire();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void BindPlayerMovementInput(UInputComponent* PlayerInputComponent);

	UTankBarrel* Barrel = nullptr;
};
