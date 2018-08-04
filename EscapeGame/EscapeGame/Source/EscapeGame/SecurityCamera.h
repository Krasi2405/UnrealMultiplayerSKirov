// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SecurityCamera.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API USecurityCamera : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USecurityCamera();

	UFUNCTION(BlueprintCallable)
	void SetupCamera(UStaticMeshComponent* HorizontalRotator, UStaticMeshComponent* VerticalRotator);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* HorizontalRotationPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* VerticalRotationPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TargetPawnCameraHeight;

private:	
	void LookAtTarget();

	UPROPERTY(EditAnywhere, Category = "Horizontal Rotation")
	float HorizontalMovementSpeedPerSecond = 90.f;

	UPROPERTY(EditAnywhere, Category = "Vertical Rotation")
	float VerticalMovementSpeedPerSecond = 30.f;

	UPROPERTY(EditAnywhere, Category = "Vertical Rotation")
	float MaxPitch = 30;

	UPROPERTY(EditAnywhere, Category = "Vertical Rotation")
	float MinPitch = -60;

	void RotateVerticalPart(float TargetValue);

	void RotateHorizontalPart(float TargetValue);
	
	
};
