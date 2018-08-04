// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankBarrel.h"



void UTankBarrel::Elevate(float TargetValue)
{
	float CurrentPitch = RelativeRotation.Pitch;
	float PitchChange = MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	if (TargetValue < CurrentPitch)
	{
		PitchChange *= -1;
	}

	float NewPitch = CurrentPitch + PitchChange;

	// Stabilize the barrel so it doesn't go back and forth between the target value each frame.
	if(CurrentPitch < TargetValue && NewPitch > TargetValue || CurrentPitch > TargetValue && NewPitch < TargetValue)
	{
		NewPitch = TargetValue;
	}

	NewPitch = FMath::Clamp(NewPitch, MinElevation, MaxElevation);
	FRotator NewRotation = FRotator(NewPitch, 0, 0);
	SetRelativeRotation(NewRotation);
}

