// Fill out your copyright notice in the Description page of Project Settings.

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
}

