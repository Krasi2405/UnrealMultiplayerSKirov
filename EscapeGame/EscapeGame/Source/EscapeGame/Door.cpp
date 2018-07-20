// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"

// Sets default values for this component's properties
UDoor::UDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoor::BeginPlay()
{
	Super::BeginPlay();

}



// Called every frame
void UDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(OpenDoorTrigger) 
	{
		OpenDoorTrigger = false;
		OpenDoor();
	}
	else if(CloseDoorTrigger) 
	{
		CloseDoorTrigger = false;
		CloseDoor();
	}
	else if(ChillTrigger)
	{
		ChillTrigger = false;
		ChillRequest.Broadcast();
	}
}


void UDoor::SetOpenDoorTrigger()
{
	if(DoorTriggersLocked != true) {
		OpenDoorTrigger = true;
	}
}

void UDoor::SetCloseDoorTrigger()
{
	if (DoorTriggersLocked != true)
	{
		CloseDoorTrigger = true;
	}
}

void UDoor::SetChillRequest() 
{
	if (DoorTriggersLocked != true)
	{
		ChillTrigger = true;
	}
}

void UDoor::OpenDoor() 
{
	/*
	AActor* Owner = GetOwner();
	FRotator* NewRotation = new FRotator(0.0f, openAngle, 0.0f);
	Owner->SetActorRotation(*NewRotation);
	*/
	UE_LOG(LogTemp, Warning, TEXT("DOOR OPENING!"))
	OpenRequest.Broadcast();
}


void UDoor::CloseDoor() 
{
	/*
	AActor* Owner = GetOwner();
	FRotator* NewRotation = new FRotator(0.0f, closedDoorAngle, 0.0f);
	Owner->SetActorRotation(*NewRotation);
	*/
	CloseRequest.Broadcast();
}


