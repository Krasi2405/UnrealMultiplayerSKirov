// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

#include "Door.h"
#include "DoorPressurePlateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UDoorPressurePlateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorPressurePlateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UDoor* DoorScript;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.4f;

	UPROPERTY(VisibleAnywhere)
	float DoorLastOpenTime;

	UPROPERTY(EditAnywhere)
	float MassActivationThreshold = 50.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	float GetTotalMassOfActorsOnPressurePlate();
	
};
