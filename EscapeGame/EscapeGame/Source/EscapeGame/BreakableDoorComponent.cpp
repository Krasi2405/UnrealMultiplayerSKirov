// Fill out your copyright notice in the Description page of Project Settings.

#include "BreakableDoorComponent.h"


// Sets default values for this component's properties
UBreakableDoorComponent::UBreakableDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBreakableDoorComponent::BeginPlay()
{
	Super::BeginPlay();

	DoorScript = GetOwner()->FindComponentByClass<UDoor>();

	UPrimitiveComponent* component = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	if (component && DoorScript) {
		component->OnComponentHit.AddDynamic(this, &UBreakableDoorComponent::OnHit);
	}
	else
	{
		if (!DoorScript)
			UE_LOG(LogTemp, Error, TEXT("%s: Door script missing!"), *GetOwner()->GetName())
		if (!component)
			UE_LOG(LogTemp, Error, TEXT("%s: Couldn't get UPrimitiveComponent!"), *GetOwner()->GetName())
	}

	
}


// Called every frame
void UBreakableDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBreakableDoorComponent::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	UE_LOG(LogTemp, Warning, TEXT("hit by %s with velocity %s!"), *OtherActor->GetName(), *OtherActor->GetVelocity().ToString())

	if (DoorKnobArea && DoorKnobArea->IsOverlappingActor(OtherActor)) {
		UE_LOG(LogTemp, Warning, TEXT("Hit on door knob by breakable door component!"))
		DoorScript->SetOpenDoorTrigger();
		DoorScript->DoorTriggersLocked = true;
	}
}

