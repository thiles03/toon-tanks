#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/TankPawn.h"
#include "ToonTanks/Pawns/TurretPawn.h"
#include "Kismet/GameplayStatics.h"

#define OUT

void ATankGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurretPawn::StaticClass(), OUT TurretActors);
    TargetTurrets = TurretActors.Num();

    PlayerTank = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATankGameModeBase::ActorDied(AActor *DeadActor)
{
    UE_LOG(LogTemp, Warning, TEXT("Pawn died"));
}

void ATankGameModeBase::HandleGameStart()
{
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
}
