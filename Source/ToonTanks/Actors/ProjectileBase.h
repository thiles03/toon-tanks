#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent *ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent *ProjectileTrail;

	UPROPERTY(EditAnywhere, Category = "Effects");
	UParticleSystem *HitParticle;

	UPROPERTY(EditAnywhere, Category = "Effects");
	USoundBase *LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Effects");
	USoundBase *HitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects");
	TSubclassOf<UCameraShake> HitShake;

	UPROPERTY(EditDefaultsOnly, Category = "Damage");
	TSubclassOf<UDamageType> DamageType;
	
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 1300.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);
};
