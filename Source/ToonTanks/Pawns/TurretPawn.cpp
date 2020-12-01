#include "TurretPawn.h"
#include "Kismet/GameplayStatics.h"
#include "TankPawn.h"

void ATurretPawn::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(FireRateTimer, this, &ATurretPawn::CheckFireCondition, FireRate, true);

    PlayerPawn = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void ATurretPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(!PlayerPawn || GetDistanceToPlayer() > FireRange)
    {
        return;
    }

    Super::RotateTurret(PlayerPawn->GetActorLocation());
}

void ATurretPawn::CheckFireCondition()
{
    // If player == null || is dead then CHECK
    if (!PlayerPawn)
    {
        return;
    }
    // If player is in range then FIRE
    if (GetDistanceToPlayer() <= FireRange)
    {
        Fire();
    }
}

float ATurretPawn::GetDistanceToPlayer()
{
    if (!PlayerPawn)
    {
        return 0.0f;
    }

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

void ATurretPawn::HandleDestruction() 
{
    // Call base pawn class to play effects
    Super::HandleDestruction();
    Destroy();
}
