#include "TankPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ATankPawn::ATankPawn()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
    Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Rotate();
    Move();

    if(PlayerControllerRef)
    {
        FHitResult TraceHit;
        PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHit);
        FVector HitLocation = TraceHitResult.ImpactPoint;

        RotateTurret(HitLocation);
    }
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ATankPawn::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn", this, &ATankPawn::CalculateRotateInput);
    PlayerInputComponent->Bindaction("Fire", IE_Pressed, this, &ATankPawn::Fire);
}

void ATankPawn::CalculateMoveInput(float Value)
{
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void ATankPawn::CalculateRotateInput(float Value)
{
    float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator Rotation = FRotator(0, RotateAmount, 0);
    RotationDirection = FQuat(Rotation);
}

void ATankPawn::Move()
{
    AddActorLocalOffset(MoveDirection, true);
}

void ATankPawn::Rotate()
{
    AddActorLocalRotation(RotationDirection, true);
}

void ATankPawn::HandleDestruction()
{
    Super::HandleDestruction();
    //Hide player
}
