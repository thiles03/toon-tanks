#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TurretPawn.generated.h"

UCLASS()
class TOONTANKS_API ATurretPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
};
