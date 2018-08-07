// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKGAME_API UTankMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SetTracksReference(UTankTrack* LeftTrack, UTankTrack* RightTrack);

	void StartThrottle();

	void StopThrottle();

	void StartNegativeThrottle();

	void StopNegativeThrottle();

	void StartTurnLeft();

	void StopTurnLeft();

	void StartTurnRight();

	void StopTurnRight();

private:

	UPROPERTY(EditAnywhere)
	UTankTrack* LeftTrack;

	UPROPERTY(EditAnywhere)
	UTankTrack* RightTrack;

	void HandleMovement();

	float LeftTrackForce = 0;

	float RightTrackForce = 0;

	bool bHasForwardThrotle = false;

	bool bHasBackwardThrotle = false;

	bool bHasLeftTorque = false;

	bool bHasRightTorque;
};
