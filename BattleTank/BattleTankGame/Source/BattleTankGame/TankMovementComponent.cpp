// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

// Sets default values for this component's properties
UTankMovementComponent::UTankMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...



}


// Called every frame
void UTankMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	HandleMovement();
}

void UTankMovementComponent::HandleMovement()
{

	if (!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("No tracks assigned for %s!"), *GetOwner()->GetName())
		return;
	}

	LeftTrackForce = 0;
	RightTrackForce = 0;
	if (bHasForwardThrotle)
	{
		LeftTrackForce = 1;
		RightTrackForce = 1;
	}
	else if (bHasBackwardThrotle)
	{
		LeftTrackForce = -1;
		RightTrackForce = -1;
	}

	if (bHasLeftTorque)
	{
		if (bHasForwardThrotle)
		{
			LeftTrackForce = 0;
		}
		else if (bHasBackwardThrotle)
		{
			RightTrackForce = 0;
		}
		else
		{
			LeftTrackForce = 1;
			RightTrackForce = -1;
		}
	}
	else if (bHasRightTorque)
	{
		if (bHasForwardThrotle)
		{
			RightTrackForce = 0.2;
		}
		else if (bHasBackwardThrotle)
		{
			LeftTrackForce = -0.2;
		}
		else
		{
			LeftTrackForce = -1;
			RightTrackForce = 1;
		}
	}

	LeftTrack->SetThrottle(LeftTrackForce);
	RightTrack->SetThrottle(RightTrackForce);

}

void UTankMovementComponent::SetTracksReference(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}


void UTankMovementComponent::StartThrottle()
{
	bHasForwardThrotle = true;
}


void UTankMovementComponent::StopThrottle()
{
	bHasForwardThrotle = false;
}


void UTankMovementComponent::StartNegativeThrottle()
{
	bHasBackwardThrotle = true;
}


void UTankMovementComponent::StopNegativeThrottle()
{
	bHasBackwardThrotle = false;
}


void UTankMovementComponent::StartTurnLeft()
{
	bHasLeftTorque = true;
}


void UTankMovementComponent::StopTurnLeft()
{
	bHasLeftTorque = false;
}


void UTankMovementComponent::StartTurnRight()
{
	bHasRightTorque = true;
}


void UTankMovementComponent::StopTurnRight()
{
	bHasRightTorque = false;
}





