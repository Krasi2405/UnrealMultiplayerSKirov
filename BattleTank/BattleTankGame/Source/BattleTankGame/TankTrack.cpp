// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Force)
{
	FVector AppliedForce = GetForwardVector() * Force * ForwardSpeed;
	FVector AppliedForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
	TankRoot->AddForceAtLocation(AppliedForce, AppliedForceLocation);
}