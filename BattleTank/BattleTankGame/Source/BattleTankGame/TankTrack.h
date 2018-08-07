// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent), ClassGroup = "TankParts")
class BATTLETANKGAME_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

	public:
		void SetThrottle(float Force);

	private:
		UPROPERTY(EditDefaultsOnly)
		float ForwardSpeed = 6000000; // = 10 ton * 6m/s

		// Way to control acceleration. Assume linear acceleration.
		UPROPERTY(EditDefaultsOnly)
		float SecondsUntilMaxSpeed = 2;
};
