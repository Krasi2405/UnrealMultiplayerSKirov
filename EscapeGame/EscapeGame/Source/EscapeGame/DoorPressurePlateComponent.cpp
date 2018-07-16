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
}


// Called every frame
void UDoorPressurePlateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (PressurePlate && GetTotalMassOfActorsOnPressurePlate() >= MassActivationThreshold) {
		DoorScript->SetOpenDoorTrigger();
		// UE_LOG(LogTemp, Warning, TEXT("Door open for %s"), *GetOwner()->GetName())
		DoorLastOpenTime = GetWorld()->GetTimeSeconds();
	}
	else if (DoorLastOpenTime + DoorCloseDelay < GetWorld()->GetTimeSeconds()) {
		// UE_LOG(LogTemp, Warning, TEXT("Door close for %s"), *GetOwner()->GetName())
		DoorScript->SetCloseDoorTrigger();
	}
}

float UDoorPressurePlateComponent::GetTotalMassOfActorsOnPressurePlate()
{
	float TotalMass = 0;

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for(const auto* Actor : OverlappingActors) {
		float ActorWeight = Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Name: %s; Weight: %f;"), *(Actor->GetName()), ActorWeight)
		TotalMass += ActorWeight;
	}


	return TotalMass;
}

