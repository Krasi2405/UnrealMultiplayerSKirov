// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "Door.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OpenDoor();

	virtual void CloseDoor();

private:

	UPROPERTY(EditAnywhere)
	float openAngle = 90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.4f;

	float DoorLastOpenTime;

	AActor* ActorThatTriggers; // Pawn inherits from actor
	AActor* ActorMasterKey;
	float GetForceApplied();

	bool doorIsBroken = false;
	
};
