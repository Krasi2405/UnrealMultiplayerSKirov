// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	ATank* ControlledTank;

	ATank* PlayerTank;

	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRate = 100;
};
