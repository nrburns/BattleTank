// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


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


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
