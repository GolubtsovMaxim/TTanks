// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"

#include "Kismet/GameplayStatics.h"
#include "TTanks/Actors/ProjectileBase.h"
#include "TTanks/Components/HealthComponent.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = CapsuleComp;
	
	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankBase"));
	BaseMeshComp->SetupAttachment(RootComponent);
	
	TurretMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	TurretMeshComp->SetupAttachment(BaseMeshComp);
	
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMeshComp);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}

void APawnBase::RotateTurret(FVector LookAt)
{

	FVector LookAtClean = FVector(LookAt.X, LookAt.Y, TurretMeshComp->GetComponentLocation().Z);
	FVector StartLocation = TurretMeshComp->GetComponentLocation();
	
	FRotator TurretRotation = FVector(LookAtClean - StartLocation).Rotation();
	TurretMeshComp->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire()
{
	if (ProjectileClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire!"));
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>
			(
				ProjectileClass, 
				ProjectileSpawnPoint->GetComponentLocation(), 
				ProjectileSpawnPoint->GetComponentRotation()
			);
		TempProjectile->SetOwner(this);
	}
	
}

void APawnBase::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
}
