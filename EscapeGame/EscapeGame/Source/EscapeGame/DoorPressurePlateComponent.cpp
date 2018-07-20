// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorPressurePlateComponent.h"


// Sets default values for this component's properties
UDoorPressurePlateComponent::UDoorPressurePlateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorPressurePlateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	DoorScript = GetOwner()->FindComponentByClass<UDoor>();

	if (!DoorScript)
		UE_LOG(LogTemp, Error, TEXT("%s: Door script missing!"), *GetOwner()->GetName())
	if (!PressurePlate)
		UE_LOG(LogTemp, Error, TEXT("%s: Pressure plate missing!"), *GetOwner()->GetName())
}


// Called every frame
void UDoorPressurePlateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PressurePlate || !DoorScript)
	{
		return;
	}

	if (GetTotalMassOfActorsOnPressurePlate() >= MassActivationThreshold) 
	{
		DoorScript->SetOpenDoorTrigger();
		DoorLastOpenTime = GetWorld()->GetTimeSeconds();
	}
	else if (DoorLastOpenTime + DoorCloseDelay < GetWorld()->GetTimeSeconds()) 
	{
		DoorScript->SetCloseDoorTrigger();
	}
	else 
	{
		DoorScript->SetChillRequest();
	}
}

float UDoorPressurePlateComponent::GetTotalMassOfActorsOnPressurePlate()
{
	float TotalMass = 0;

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for(const auto* Actor : OverlappingActors) 
	{
		float ActorWeight = Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Name: %s; Weight: %f;"), *(Actor->GetName()), ActorWeight)
		TotalMass += ActorWeight;
	}


	return TotalMass;
}

