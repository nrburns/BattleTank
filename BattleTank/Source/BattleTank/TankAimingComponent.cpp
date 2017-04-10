// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrel(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UTankAimingComponent::SetTurret(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(const FVector& Location, float LaunchSpeed) const
{
	if (Barrel != nullptr && Turret != nullptr)
	{
		FVector LaunchVelocity;
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

		if (UGameplayStatics::SuggestProjectileVelocity(
			this,
			LaunchVelocity,
			StartLocation,
			Location,
			LaunchSpeed,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace
		))
		{
			MoveBarrelTowards(LaunchVelocity.GetSafeNormal());
		}
	}
}


void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection) const
{
	FRotator AimAsRotator = AimDirection.Rotation();

	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator DeltaBarrelRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaBarrelRotator.Pitch);

	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator DeltaTurretRotator = AimAsRotator - TurretRotator;
	Turret->Rotate(DeltaTurretRotator.Yaw);
}
