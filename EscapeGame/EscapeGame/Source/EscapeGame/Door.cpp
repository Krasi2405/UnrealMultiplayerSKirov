// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "GameFramework/Actor.h"

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
	
	ActorThatTriggers = GetWorld()->GetFirstPlayerController()->GetPawn();
	AActor* owner = GetOwner();
	UPrimitiveComponent* component = owner->FindComponentByClass<UPrimitiveComponent>();
	if (component) {
		UE_LOG(LogTemp, Warning, TEXT("Registered hit event on door!"))
		component->OnComponentHit.AddDynamic(this, &UDoor::OnHit);
	}
}

void UDoor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	UE_LOG(LogTemp, Warning, TEXT("hit!"))
}

// Called every frame
void UDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (doorIsBroken) return;

	if (PressurePlate && ActorMasterKey && PressurePlate->IsOverlappingActor(ActorMasterKey)) {
		OpenDoor();
		UE_LOG(LogTemp, Warning, TEXT("Open Door!"));
		DoorLastOpenTime = GetWorld()->GetTimeSeconds();
	}
	else if(DoorLastOpenTime + DoorCloseDelay < GetWorld()->GetTimeSeconds()){
		UE_LOG(LogTemp, Warning, TEXT("Close Door!"));
		CloseDoor();
	}
	/*
	else if (PressurePlate && ActorThatTriggers && GetForceApplied() > 50.0f) {
		OpenDoor();
		doorIsBroken = true;
	}
	*/
	///
	//UPhysicsCollisionHandler collisionHandler;
}


float UDoor::GetForceApplied() {
	return 60.f;
}


void UDoor::OpenDoor() {
	AActor* Owner = GetOwner();
	FRotator* NewRotation = new FRotator(0.0f, openAngle, 0.0f);
	Owner->SetActorRotation(*NewRotation);
}


void UDoor::CloseDoor() {
	AActor* Owner = GetOwner();
	FRotator* NewRotation = new FRotator(0.0f, openAngle - 90.0f, 0.0f);
	Owner->SetActorRotation(*NewRotation);
}
