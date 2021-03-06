// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTank;
class APawnTurret;
class APlayerControllerBase;

UCLASS()
class TTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void OnActorDied(AActor* DiedActor);
        
protected:

        virtual void BeginPlay() override;

        UFUNCTION(BlueprintImplementableEvent)
        void GameStart();
        UFUNCTION(BlueprintImplementableEvent)
        void GameOver(bool PlayerWon);
        UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
            int32 StartDelay = 3;

private:

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

    APawnTank* PlayerTank{nullptr};
    uint32 TargetTurrets = 0;
    uint32 GetTargetTurrets() const;
    APlayerControllerBase* PlayerController;

    

};
