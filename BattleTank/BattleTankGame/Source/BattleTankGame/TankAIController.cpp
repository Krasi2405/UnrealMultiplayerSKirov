// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlTank();
	if (ControlledTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController possessing %s"), *ControlledTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No AI tank!"))
	}

	ATank* PlayerTank = GetPlayer();
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

}


ATank* ATankAIController::GetControlTank() const
{
	return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayer() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	return Cast<ATank>(PlayerController->GetPawn());
}