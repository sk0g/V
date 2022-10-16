#include "Core/VCharacter.h"

#include "ActorComponents/VInteractionComponent.h"
#include "Combat/VProjectile.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "VData.h"

AVCharacter::AVCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmC = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraC	   = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	SpringArmC->SetupAttachment(RootComponent);
	CameraC->SetupAttachment(SpringArmC);

	InteractionC = CreateDefaultSubobject<UVInteractionComponent>("InteractionComponent");
}

void AVCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVCharacter::BeginPlay()
{
	Super::BeginPlay();
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

	PlayerInputComponent->BindAction("Interact", IE_Pressed, InteractionC, &UVInteractionComponent::Interact);

	PlayerInputComponent->BindAction<FAttackDelegate>(
		"AttackPrimary", IE_Pressed, this, &AVCharacter::Attack, EAbilitySlot::Primary);
	PlayerInputComponent->BindAction<FAttackDelegate>(
		"AttackSecondary", IE_Pressed, this, &AVCharacter::Attack, EAbilitySlot::Secondary);
	PlayerInputComponent->BindAction<FAttackDelegate>(
		"AttackTertiary", IE_Pressed, this, &AVCharacter::Attack, EAbilitySlot::Tertiary);
}

void AVCharacter::CleanSpawnedProjectiles()
{
	for (auto Projectile : SpawnedProjectiles)
	{
		if (IsValid(Projectile)) { continue; }

		SpawnedProjectiles.Remove(Projectile);
	}
}

void AVCharacter::MoveForward(float Value)
{
	auto ForwardVector = GetControlRotation().Vector();
	AddMovementInput(ForwardVector, Value);
}

void AVCharacter::MoveRight(float Value)
{
	auto RightVector = GetControlRotation().RotateVector(FVector::RightVector);
	AddMovementInput(RightVector, Value);
}

void AVCharacter::Attack(EAbilitySlot Slot)
{
	ensureAlways(Projectiles.Contains(Slot) and IsValid(Projectiles.Find(Slot)->Get()));
	CleanSpawnedProjectiles();

	// If projectile to be spawned supports early termination, check if there is one to be terminated first
	auto ProjectileToSpawn = Projectiles.Find(Slot);
	if (ProjectileToSpawn->GetDefaultObject()->bSupportsEarlyTermination)
	{
		for (auto Projectile : SpawnedProjectiles)
		{
			if (not Projectile->bSupportsEarlyTermination) { continue; }
			if (Projectile->GetClass()->GetDefaultObject() != ProjectileToSpawn->GetDefaultObject()) { continue; }

			Projectile->SelfDestruct();
			return;
		}
	}

	// Otherwise, continue to actually spawning the actor
	FVector RightHandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	auto SpawnTransform		  = FTransform(GetControlRotation(), RightHandLocation);

	auto ProjectileRotation = GetCompensatedProjectileLaunchRotation(SpawnTransform.GetLocation());
	if (ProjectileRotation != FRotator::ZeroRotator) { SpawnTransform.SetRotation(ProjectileRotation.Quaternion()); }

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator					   = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	auto SpawnedActor =
		GetWorld()->SpawnActor<AVProjectile>(Projectiles.Find(Slot)->Get(), SpawnTransform, SpawnParams);
	SpawnedActor->SetInstigator(this);

	SpawnedProjectiles.Add(SpawnedActor);
}

FRotator AVCharacter::GetCompensatedProjectileLaunchRotation(FVector LaunchLocation) const
{
	FHitResult Hit;
	FVector TraceStart = CameraC->GetComponentLocation();
	FVector TraceEnd   = TraceStart + (CameraC->GetComponentRotation().Vector() * 200000.f);

	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility);

	if (Hit.Distance == 0) { return FRotator::ZeroRotator; }

	return (Hit.Location - LaunchLocation).Rotation();
}