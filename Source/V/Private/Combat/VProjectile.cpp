#include "Combat/VProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

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

	MovementC				= CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementC->InitialSpeed = ForwardMovementSpeed;
	MovementC->bRotationFollowsVelocity		= true;
	MovementC->bInitialVelocityInLocalSpace = true;
	if (not bAffectedByGravity) { MovementC->ProjectileGravityScale = 0.f; }
}

void AVProjectile::BeginPlay()
{
	Super::BeginPlay();

	EnableCollision();
}

FAsyncCoroutine AVProjectile::EnableCollision()
{
	if (not bCanCollide) { co_return; }

	// rough body radius margin / movement speed should work - unless you are moving forward while you're shooting...
	auto WaitFor = 200.f / ForwardMovementSpeed;
	co_await Latent::Seconds(WaitFor);

	SphereC->SetCollisionProfileName("Projectile");
}

void AVProjectile::SetInstigator(AActor* Actor)
{
	FiredBy = Actor;

	if (bCanCollide) { SphereC->IgnoreActorWhenMoving(Actor, true); }
}