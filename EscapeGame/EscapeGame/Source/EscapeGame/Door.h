// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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

	UPROPERTY(EditAnywhere)
	bool DoorTriggersLocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door rotation")
	float RotationDuration = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door rotation")
	float RotationAngle = 90;

	virtual void OpenDoor();

	virtual void CloseDoor();

	void SetOpenDoorTrigger();

	void SetCloseDoorTrigger();

	void SetChillRequest();

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OpenRequest;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent CloseRequest;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent ChillRequest;


private:

	UPROPERTY(EditAnywhere)
	bool OpenDoorTrigger = false;

	UPROPERTY(EditAnywhere)
	bool CloseDoorTrigger = true;

	UPROPERTY(EditAnywhere)
	bool ChillTrigger = true;
	/*
	UPROPERTY(EditAnywhere)
	AActor* ActorMasterKey;
	*/
	

};
