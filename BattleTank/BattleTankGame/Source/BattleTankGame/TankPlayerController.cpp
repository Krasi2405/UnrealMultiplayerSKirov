// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "UObject/UObjectGlobals.h"
#include "Components/InputComponent.h"
#include "SStandardSlateWidget.h"
#include "SlateOptMacros.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	

	ControlledTank = Cast<ATank>(GetPawn());
	if(!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("No tank!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possessing %s"), *ControlledTank->GetName())
	}

	CreatePlayerUI();
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


void ATankPlayerController::CreatePlayerUI()
{
	if (wPlayerUI)
	{
		PlayerUI = CreateWidget<UUserWidget>(this, wPlayerUI);
		if (PlayerUI)
		{
			PlayerUI->AddToViewport();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Main menu widget!"))
	}
}


FVector2D ATankPlayerController::GetAimingReticlePosition() const
{
	UWidget* AimingReticle = PlayerUI->GetWidgetFromName("AimingReticle");
	if (AimingReticle)
	{
		UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(AimingReticle);
		float Scale = UWidgetLayoutLibrary::GetViewportScale(GetWorld()->GetGameViewport());
		int ViewportX;
		int ViewportY;
		GetViewportSize(ViewportX, ViewportY);
		FVector2D CanvasSlotPosition = CanvasSlot->GetPosition();
		FVector2D Position = {ViewportX / 2.f, ViewportY / 3.f};
		FVector2D PositionTest = { ViewportX / 2 + CanvasSlotPosition.X * Scale, ViewportY / 2 + CanvasSlotPosition.Y * Scale };
		return PositionTest;
	}
	return FVector2D::ZeroVector;
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ControlledTank) return;

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) 
	{
		ControlledTank->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	HitLocation = FVector::ForwardVector;
	FVector2D ScreenLocation = GetAimingReticlePosition();

	FVector CameraWorldLocation;
	FVector CameraDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, CameraDirection)) 
	{
		if(GetLookVectorHitLocation(CameraWorldLocation, CameraDirection, HitLocation)) 
		{
			return true;
		}
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector Start, FVector Direction, FVector &HitLocation) const
{
	FHitResult OutResult;
	FCollisionQueryParams CollisionQuery = { "", false, ControlledTank };

	bool bHasHit = GetWorld()->LineTraceSingleByChannel(
		OutResult,
		Start,
		Start + Direction * LineTraceRange,
		ECC_Visibility,
		CollisionQuery
	);


	if(bHasHit)
	{
		HitLocation = OutResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector::ZeroVector;
		return false;
	}
}