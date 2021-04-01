// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "PawnTank.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || CalculateDistanceToPlayer() > FireRange || !PlayerPawn->GetIsAlive())
	{
		return;
	}

	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	if (!PlayerPawn || !PlayerPawn->GetIsAlive())
	{
		return;
	}
	
	if (CalculateDistanceToPlayer() <= FireRange)
	{
		Fire();
	}
}

float APawnTurret::CalculateDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0.f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}
