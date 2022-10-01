#include "Core/VCharacter.h"

#include "ActorComponents/VInteractionComponent.h"
#include "Combat/VProjectile.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AVCharacter::AVCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmC = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraC	   = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	SpringArmC->SetupAttachment(RootComponent);
	CameraC->SetupAttachment(SpringArmC);

	InteractionC = CreateDefaultSubobject<UVInteractionComponent>("InteractionComponent");
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

void AVCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AVCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("AttackPrimary", IE_Pressed, this, &AVCharacter::AttackPrimary);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, InteractionC, &UVInteractionComponent::Interact);
}
