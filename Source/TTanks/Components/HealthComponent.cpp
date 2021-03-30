// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Kismet/GameplayStatics.h"
#include "TTanks/GameModes/TankGameModeBase.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrentHealth = DefaultHealth;
    GameMode = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor *DamagedActor, float Damage, const UDamageType* DamageType, AController *InstigatedBy, AActor *DamageCauser)
{
    if (Damage == 0.f || CurrentHealth <= 0.f) 
    {
      return;
    }

    CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, DefaultHealth);

    if (CurrentHealth <= 0.f) 
    {
        if (GameMode) 
        {
            GameMode->OnActorDied(GetOwner());
        }
        else 
        {
            UE_LOG(LogTemp, Warning, TEXT("Health Component has no reference to the GameMode"));
        }
    }
}
