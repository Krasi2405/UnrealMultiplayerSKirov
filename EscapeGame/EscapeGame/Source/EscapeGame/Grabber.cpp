// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"



// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandleComponent->GrabbedComponent) 
	{
		// Move object that's being hold
		PhysicsHandleComponent->SetTargetLocation(GetReachEnd());
	}
}


void UGrabber::FindPhysicsHandleComponent() {
	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandleComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no physics handler!"), *(GetOwner()->GetName()))
	}
}


void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no Input Component!"), *(GetOwner()->GetName()))
	}
}


void UGrabber::Grab() {
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();
	if (ActorHit && ComponentToGrab)
	{
		PhysicsHandleComponent->GrabComponentAtLocation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("Grabber raycast hit: %s"), *(ActorHit->GetName()))
	}
}


void UGrabber::Release() {
	PhysicsHandleComponent->ReleaseComponent();
}


UGrabber::FPlayerOrientation UGrabber::GetPlayerOrientation() {
	FPlayerOrientation PlayerOrientation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerOrientation.PlayerViewPointLocation,
		OUT PlayerOrientation.PlayerViewPointRotation
	);
	return PlayerOrientation;
}


FVector UGrabber::GetReachStart() {
	return GetPlayerOrientation().PlayerViewPointLocation;
}

FVector UGrabber::GetReachEnd() {
	FPlayerOrientation PlayerOrientation = GetPlayerOrientation();
	FVector ReachEnd = PlayerOrientation.PlayerViewPointLocation + PlayerOrientation.PlayerViewPointRotation.Vector() * Reach;
	return ReachEnd;
}


FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachStart(),
		GetReachEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	return HitResult;
}