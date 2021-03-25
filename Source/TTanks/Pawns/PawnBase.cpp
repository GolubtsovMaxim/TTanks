// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
//#include "Pawns/PawnBase.h"

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

}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

