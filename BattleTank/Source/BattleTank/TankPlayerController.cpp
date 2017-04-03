// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *(ControlledTank->GetName()));
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardCrosshair() const
{
	if (GetControlledTank() != nullptr)
	{
		FVector HitLocation;
		if (GetSightRayHitLocation(HitLocation))
		{
			GetControlledTank()->AimAt(HitLocation);
		}
	}
}


bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	FVector WorldDirection;
	if (GetWorldDirection(ScreenLocation, WorldDirection))
	{
		return GetWorldDirectionHitLocation(HitLocation, WorldDirection);
	}

	return false;
}


bool ATankPlayerController::GetWorldDirection(const FVector2D& ScreenLocation, FVector& WorldDirection) const
{
	FVector WorldLocation;  // Not needed
	return DeprojectScreenPositionToWorld(ScreenLocation.X,
										  ScreenLocation.Y, 
										  WorldLocation,
										  WorldDirection);
}


bool ATankPlayerController::GetWorldDirectionHitLocation(FVector& HitLocation, const FVector& WorldDirection) const
{
	FHitResult HitResult;
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + (WorldDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility
	))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}
