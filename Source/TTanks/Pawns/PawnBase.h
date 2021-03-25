// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "PawnBase.generated.h"

UCLASS()
class TTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY()
	UCapsuleComponent* CapsuleComp;

	UPROPERTY()
	UStaticMeshComponent* BaseMeshComp;

	UPROPERTY()
	UStaticMeshComponent* TurretMeshComp;

	UPROPERTY()
	USceneComponent* ProjectileSpawnPoint;
	
};
