// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"



void UTankTurret::Rotate(float TargetValue)
{
	float Yaw = RelativeRotation.Yaw;
	float YawChange = MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewYaw;

	// Edge case of positive rotation of barrel having to go into negative.
	if(Yaw >= 0.f && TargetValue < 0)
	{
		if(Yaw - TargetValue > 180) 
		{
			NewYaw = Yaw + YawChange;
		}
		else
		{
			NewYaw = Yaw - YawChange;
		}
	}
	// Edge case of negative rotation of barrel having to go into positive.
	else if (Yaw < 0.f && TargetValue > 0)
	{
		if (TargetValue - Yaw > 180)
		{
			NewYaw = Yaw - YawChange;
		}
		else
		{
			NewYaw = Yaw + YawChange;
		}
	}
	// Normal turret rotation
	else
	{
		if (Yaw > TargetValue)
		{
			NewYaw = Yaw - YawChange;
		}
		else
		{
			NewYaw = Yaw + YawChange;
		}
	}

	// Stabilize Rotation;
	if (Yaw < TargetValue && NewYaw > TargetValue || Yaw > TargetValue && NewYaw < TargetValue)
	{
		NewYaw = TargetValue;
	}
	FRotator NewRotation = { 0, NewYaw, 0 };
	SetRelativeRotation(NewRotation);
}

