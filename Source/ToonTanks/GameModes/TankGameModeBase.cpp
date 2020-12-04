#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/TankPawn.h"
#include "ToonTanks/Pawns/TurretPawn.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

#define OUT

void ATankGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor *DeadActor)
{
    // Is the dead actor the player
    if (DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);

        // Disable player controls
        if (PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);
        }
    }
    // Is the dead actor a turret
    else if (ATurretPawn *DestroyedTurret = Cast<ATurretPawn>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();

        // No more turrets? Game won
        if (--TargetTurrets == 0)
        {
            HandleGameOver(true);
        }
    }
}

void ATankGameModeBase::HandleGameStart()
{
    // Get turret, player and player controller references
    TargetTurrets = GetTargetTurretCount();
    PlayerTank = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

    GameStart();

    // Disable player controls for duration of start timer
    if (PlayerControllerRef)
    {
        PlayerControllerRef->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableHandle;
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(
            PlayerControllerRef, 
            &APlayerControllerBase::SetPlayerEnabledState, 
            true);

        GetWorld()->GetTimerManager().SetTimer(
            PlayerEnableHandle, 
            PlayerEnableDelegate, 
            StartDelay, 
            false);
    }
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
    GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurretPawn::StaticClass(), OUT TurretActors);
    return TurretActors.Num();
}
