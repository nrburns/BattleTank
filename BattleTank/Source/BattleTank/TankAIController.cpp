// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank != nullptr)
	{
		ATank* PlayerTank = GetPlayerTank();
		if (PlayerTank != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("AIController found Player Tank %s"), *(PlayerTank->GetName()));
		}
	}
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtPlayer();
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


void ATankAIController::AimAtPlayer() const
{
	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank != nullptr)
	{
		ATank* PlayerTank = GetPlayerTank();
		if (PlayerTank != nullptr)
		{
			ControlledTank->AimAt(PlayerTank->GetActorLocation());
		}
	}
}
