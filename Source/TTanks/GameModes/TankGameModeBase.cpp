// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "TTanks/Pawns/PawnTank.h"
#include "TTanks/Pawns/PawnTurret.h"
#include "TTanks/PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
    Super::BeginPlay();
	
    HandleGameStart();
}

void ATankGameModeBase::OnActorDied(AActor *DiedActor)
{
	if (DiedActor == PlayerTank)
	{
        PlayerTank->HandleDestruction();
        HandleGameOver(false);

		if (PlayerController)
		{
            PlayerController->SetPlayerEnabledState(false);
		}
		
        UE_LOG(LogTemp, Warning, TEXT("Player died"));
	}
    else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DiedActor))
    {
        DestroyedTurret->HandleDestruction();
        //TargetTurrets--;
        UE_LOG(LogTemp, Warning, TEXT("Turret died"));
    	if (--TargetTurrets == 0)
    	{
            HandleGameOver(true);
            UE_LOG(LogTemp, Warning, TEXT("Game over. Player Won"));
    	}
    }
    
}

void ATankGameModeBase::HandleGameStart()
{
    TargetTurrets = GetTargetTurrets();
    PlayerTank = Cast<APawnTank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    PlayerController = Cast<APlayerControllerBase>(GetWorld()->GetFirstPlayerController());
    GameStart();

    if (PlayerController)
    {
        PlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnable;
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(
            PlayerController, &APlayerControllerBase::SetPlayerEnabledState, true);

        GetWorld()->GetTimerManager().SetTimer(PlayerEnable, PlayerEnableDelegate, StartDelay, false);
    }
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
    GameOver(PlayerWon);
}

uint32 ATankGameModeBase::GetTargetTurrets() const
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    return  TurretActors.Num();
}
