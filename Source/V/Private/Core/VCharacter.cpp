#include "Core/VCharacter.h"

#include "Camera/CameraComponent.h"
#include "Combat/VProjectile.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AVCharacter::AVCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmC = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraC	   = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	SpringArmC->SetupAttachment(RootComponent);
	CameraC->SetupAttachment(SpringArmC);
}

void AVCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AVCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AVCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AVCharacter::AttackPrimary()
{
	FVector RightHandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	auto SpawnTransform		  = FTransform(GetActorRotation(), RightHandLocation);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(PrimaryProjectile, SpawnTransform, SpawnParameters);
}

// Called to bind functionality to input
void AVCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AVCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("AttackPrimary", IE_Pressed, this, &AVCharacter::AttackPrimary);
}
