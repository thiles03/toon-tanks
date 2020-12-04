#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class AProjectileBase;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	void PawnDestroyed();
	virtual void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent *CapsuleComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *BaseMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *TurretMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *ProjectileSpawnPoint = nullptr;
	//VARIABLES
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass;
};
