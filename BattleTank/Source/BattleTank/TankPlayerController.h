// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;

	void AimTowardCrosshair() const;
	
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetWorldDirection(const FVector2D& ScreenLocation, FVector& WorldDirection) const;
	bool GetWorldDirectionHitLocation(FVector& HitLocation, const FVector& WorldDirection) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f;

	float LineTraceRange = 1000000;  // centimetres
};
