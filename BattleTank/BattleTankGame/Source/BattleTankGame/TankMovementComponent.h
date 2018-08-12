// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
class UTankTrack;

UCLASS()
class BATTLETANKGAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	

	public:
		// Sets default values for this component's properties
		UTankMovementComponent();

		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		void HorizontalMovement(float Value);
		
		void VerticalMovement(float Value);

		UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTracksReference(UTankTrack* LeftTrack, UTankTrack* RightTrack);

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

		void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	private:

		UPROPERTY(EditAnywhere)
		UTankTrack* LeftTrack;

		UPROPERTY(EditAnywhere)
		UTankTrack* RightTrack;

		void HandleMovement();

		float LeftTrackForce = 0;

		float RightTrackForce = 0;
};
