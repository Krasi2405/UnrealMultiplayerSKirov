// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"



UCLASS()
class BATTLETANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> wPlayerUI;

		// Variable to hold the widget After Creating it.
		UUserWidget* PlayerUI;

	protected:
		UPROPERTY(BlueprintReadOnly)
		ATank* ControlledTank;

		void BeginPlay() override;

		void Tick(float DeltaTime) override;

		void CreatePlayerUI();

	private:
		float LineTraceRange = 1000000;

		void AimTowardsCrosshair();

		FVector2D GetAimingReticlePosition() const;

		bool GetSightRayHitLocation(FVector &HitLocation) const;

		bool GetLookVectorHitLocation(FVector Start, FVector Direction, FVector &HitLocation) const;

};
