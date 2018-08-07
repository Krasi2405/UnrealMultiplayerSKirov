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

	LeftTrack->SetThrottle(LeftTrackForce);
	RightTrack->SetThrottle(RightTrackForce);

	LeftTrackForce = 0;
	RightTrackForce = 0;
}

void UTankMovementComponent::HorizontalMovement(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Horizontal value: %f"), Value);
	if(Value < 0)
	{
		RightTrackForce += Value / 2;
		LeftTrackForce -= Value / 2;
	}
	else
	{
		RightTrackForce -= Value / 2;
		LeftTrackForce += Value / 2;
	}
}

void UTankMovementComponent::VerticalMovement(float Value) 
{
	LeftTrackForce += Value;
	RightTrackForce += Value;
	UE_LOG(LogTemp, Warning, TEXT("Vertical value: %f"), Value);
}


void UTankMovementComponent::SetTracksReference(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	if(!LeftTrack || !RightTrack) return;
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}





