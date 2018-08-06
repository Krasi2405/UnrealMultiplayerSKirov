// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Force)
{
	UE_LOG(LogTemp, Warning, TEXT("%s track force: %f"), *GetName(), Force)
}