#include "TurretPawn.h"
#include "Kismet/GameplayStatics.h"

void ATurretPawn::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ATurretPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    GetWorldTimerManager().SetTimer(FireRateTimer, this, &ATurretPawn::CheckFireCondition, FireRate, true);
}

void ATurretPawn::CheckFireCondition() 
{
    
}