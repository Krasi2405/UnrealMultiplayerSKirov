// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());
	if (ControlledTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController possessing %s"), *ControlledTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No AI tank!"))
	}


	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerTank = Cast<ATank>(PlayerController->GetPawn());
	if(PlayerTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found player %s"), *PlayerTank->GetName())
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController didnt find player"))
	}
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO: Fix acceptance rate.
	MoveToActor(PlayerTank, AcceptanceRate);

	ControlledTank->AttemptFire();
	ControlledTank->AimAt(PlayerTank->GetActorLocation());
}