#include "Combat/VProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

constexpr float PROJECTILE_COLLISION_ENABLE_DISTANCE = 200.f;

AVProjectile::AVProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereC = CreateDefaultSubobject<USphereComponent>("SphereComponent");

	RootComponent = SphereC;

	ProjectileParticleC = CreateDefaultSubobject<UParticleSystemComponent>("ProjectileParticle");
	ProjectileParticleC->SetupAttachment(SphereC);

	HitParticleC = CreateDefaultSubobject<UParticleSystemComponent>("HitParticle");
	HitParticleC->SetAutoActivate(false);
	HitParticleC->SetupAttachment(SphereC);

	MovementC = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	SetupMovementComponent();
}

void AVProjectile::BeginPlay()
{
	Super::BeginPlay();

	EnableCollision();

	ScheduleExpiry();
}

void AVProjectile::SetupMovementComponent()
{
	MovementC->InitialSpeed					= ForwardMovementSpeed;
	MovementC->bRotationFollowsVelocity		= true;
	MovementC->bInitialVelocityInLocalSpace = true;
	if (not bAffectedByGravity) { MovementC->ProjectileGravityScale = 0.f; }
}

FAsyncCoroutine AVProjectile::EnableCollision()
{
	if (not bCanCollide) { co_return; }

	// rough body radius + margin / movement speed should work
	// unless you are moving forward while you're shooting...
	auto WaitFor = PROJECTILE_COLLISION_ENABLE_DISTANCE / ForwardMovementSpeed;
	co_await Latent::Seconds(WaitFor);

	SphereC->SetCollisionProfileName("Projectile");
}

FAsyncCoroutine AVProjectile::ScheduleExpiry()
{
	if (Lifetime <= 0.f) { co_return; }

	co_await Latent::Seconds(Lifetime);
	if (this->IsActorBeingDestroyed()) { co_return; }

	SelfDestruct();
}

void AVProjectile::SetInstigator(AActor* Actor)
{
	FiredBy = Actor;

	if (bCanCollide) { SphereC->IgnoreActorWhenMoving(Actor, true); }
}