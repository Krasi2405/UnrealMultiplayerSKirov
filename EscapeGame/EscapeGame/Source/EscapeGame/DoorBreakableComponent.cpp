// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorBreakableComponent.h"


// Sets default values for this component's properties
UDoorBreakableComponent::UDoorBreakableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UDoorBreakableComponent::BeginPlay()
{
	Super::BeginPlay();


	AActor* player = GetWorld()->GetFirstPlayerController()->GetPawn();
	IgnoreActors.Add(player);

	DoorScript = GetOwner()->FindComponentByClass<UDoor>();

	UPrimitiveComponent* component = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	if (component && DoorScript) {
		component->OnComponentHit.AddDynamic(this, &UDoorBreakableComponent::OnHit);
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
void UDoorBreakableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDoorBreakableComponent::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	
	if (DoorBroke) return;

	if (DoorKnobArea && DoorKnobArea->IsOverlappingActor(OtherActor)) {

		for(int i = 0; i < IgnoreActors.Num(); i++) 
		{
			if(IgnoreActors[i] == OtherActor) 
			{
				return;
			}
		}


		FVector FrontVector = GetOwner()->GetActorForwardVector();
		FVector ForceVector = OtherActor->GetVelocity().ProjectOnTo(FrontVector);
		
		UE_LOG(LogTemp, Warning, TEXT("Force Vector: %s"), *ForceVector.ToString())

		// Divide by 100 because Unreal units are centimeters and Force = Mass(kg) * Velocity(m/s)
		float ImpactForce =
			OtherActor->FindComponentByClass<UPrimitiveComponent>()->GetMass() *
			FMath::Sqrt(ForceVector.SizeSquared()) / 100;
			

		if (ImpactForce >= ForceToBreak)
		{
			UE_LOG(LogTemp, Warning, TEXT("Door broke with a force of %f newtons"), ImpactForce)
			DoorScript->SetOpenDoorTrigger();
			DoorScript->DoorTriggersLocked = true;
			DoorBroke = true;
		}
	}
}

