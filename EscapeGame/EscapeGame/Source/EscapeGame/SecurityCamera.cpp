// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "SecurityCamera.h"


// Sets default values for this component's properties
USecurityCamera::USecurityCamera()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USecurityCamera::BeginPlay()
{
	Super::BeginPlay();

	Target = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator();
	APawn *pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (pawn) 
	{
		TargetPawnCameraHeight = pawn->BaseEyeHeight;
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Player not controlling a pawn."))
	}
}


// Called every frame
void USecurityCamera::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	LookAtTarget();
}


void USecurityCamera::SetupCamera(UStaticMeshComponent* HorizontalRotator, UStaticMeshComponent* VerticalRotator)
{
	if (HorizontalRotator)
	{
		HorizontalRotationPoint = HorizontalRotator;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Security Camera has no Horizontal Rotator StaticMeshComponent assigned!"));
	}

	if (VerticalRotator)
	{
		VerticalRotationPoint = VerticalRotator;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Security Camera has no Vertical Rotator StaticMeshComponent assigned!"));
	}
}


void USecurityCamera::LookAtTarget()
{
	FVector PlayerLocation = Target->GetActorLocation();
	PlayerLocation.Z += TargetPawnCameraHeight;
	FRotator VerticalRotation = UKismetMathLibrary::FindLookAtRotation(
		VerticalRotationPoint->GetComponentLocation(),
		PlayerLocation
	);

	FRotator HorizontalRotation = UKismetMathLibrary::FindLookAtRotation(
		HorizontalRotationPoint->GetComponentLocation(),
		Target->GetActorLocation()
	);

	if(VerticalRotationPoint)
		RotateVerticalPart(VerticalRotation.Pitch);

	if(HorizontalRotationPoint)
		RotateHorizontalPart(HorizontalRotation.Yaw);
}


void USecurityCamera::RotateVerticalPart(float TargetValue)
{
	float Pitch = VerticalRotationPoint->RelativeRotation.Pitch;
	float PitchChange = VerticalMovementSpeedPerSecond * GetWorld()->DeltaTimeSeconds;
	if (TargetValue < Pitch) PitchChange *= -1;

	float NewPitch = Pitch + PitchChange;

	NewPitch = FMath::Clamp(NewPitch, MinPitch, MaxPitch);

	// Stabilize Rotation;
	if (Pitch < TargetValue && NewPitch > TargetValue || Pitch > TargetValue && NewPitch < TargetValue)
	{
		NewPitch = TargetValue;
	}


	VerticalRotationPoint->SetRelativeRotation(FRotator(NewPitch, 0, 0));
}


void USecurityCamera::RotateHorizontalPart(float TargetValue)
{
	float Yaw = HorizontalRotationPoint->RelativeRotation.Yaw;
	float YawChange = HorizontalMovementSpeedPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewYaw;

	if (Yaw >= 0.f && TargetValue < 0)
	{
		if (Yaw - TargetValue > 180)
		{
			NewYaw = Yaw + YawChange;
		}
		else
		{
			NewYaw = Yaw - YawChange;
		}
	}
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

	HorizontalRotationPoint->SetRelativeRotation(FRotator(0, NewYaw, 0));
}
