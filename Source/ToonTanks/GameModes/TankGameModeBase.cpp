#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/TankPawn.h"
#include "ToonTanks/Pawns/TurretPawn.h"
#include "Kismet/GameplayStatics.h"

#define OUT

void ATankGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor *DeadActor)
{
    if (DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);
    }
    else if (ATurretPawn *DestroyedTurret = Cast<ATurretPawn>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();

        if (--TargetTurrets == 0)
        {
            HandleGameOver(true);
        }
    }
}

void ATankGameModeBase::HandleGameStart()
{
    TargetTurrets = GetTargetTurretCount();
    PlayerTank = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

    GameStart();
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
