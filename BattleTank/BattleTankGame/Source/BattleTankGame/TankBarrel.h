// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (TankParts), meta = (BlueprintSpawnableComponent))
class BATTLETANKGAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()


	public:
		void Elevate(float TargetValue);
	
	private:
		UPROPERTY(EditAnywhere)
		float MaxDegreesPerSecond = 15;

		UPROPERTY(EditAnywhere)
		float MaxElevation = 25.f;

		UPROPERTY(EditAnywhere)
		float MinElevation = -5.f;

};
