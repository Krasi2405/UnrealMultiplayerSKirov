// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float TargetValue)
{
	float Yaw = RelativeRotation.Yaw;
	float YawChange = MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewYaw;

	// TODO: Rework this monstrosity.
	// Could not work out how to create an elegant solution.
	// So heres a piece of shit that works:
	if(Yaw >= 0.f)
	{
		if(TargetValue < 0)
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
		else
		{
			if(Yaw > TargetValue)
			{
				NewYaw = Yaw - YawChange;
			}
			else
			{
				NewYaw = Yaw + YawChange;
			}
			
		}
	}
	else
	{
		if(TargetValue > 0)
		{
			if(TargetValue - Yaw > 180)
			{
				NewYaw = Yaw - YawChange;
			}
			else
			{
				NewYaw = Yaw + YawChange;
			}
		}
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
	}

	// Stabilize Rotation;
	if (Yaw < TargetValue && NewYaw > TargetValue || Yaw > TargetValue && NewYaw < TargetValue)
	{
		NewYaw = TargetValue;
	}
	FRotator NewRotation = { 0, NewYaw, 0 };
	SetRelativeRotation(NewRotation);
}

