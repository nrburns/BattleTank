// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


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
			UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *(HitLocation.ToString()));
		}
	}
}


bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	if (GetControlledTank() != nullptr)
	{
		FVector Start = GetPawn()->GetActorLocation();
		HitLocation = Start + PlayerCameraManager->GetCameraRotation().Vector() * 1000;

		return true;
	}

	return false;
}
