// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> wPlayerUI;

		// Variable to hold the widget After Creating it.
		UUserWidget* PlayerUI;

		void BeginPlay() override;

		void CreatePlayerUI();

		void Tick(float DeltaTime) override;

	private:
		float LineTraceRange = 1000000;

		void AimTowardsCrosshair();

		FVector2D GetAimingReticlePosition() const;

		ATank* GetControlTank() const;

		bool GetSightRayHitLocation(FVector &HitLocation) const;

		bool GetLookVectorHitLocation(FVector Start, FVector Direction, FVector &HitLocation) const;

};
