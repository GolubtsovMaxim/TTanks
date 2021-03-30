// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;
/**
 * 
 */
UCLASS()
class TTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void HandleDestruction() override;
	
private:
	
	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 50.f;

	APawnTank* PlayerPawn;

	void CheckFireCondition();

	float CalculateDistanceToPlayer();
};
