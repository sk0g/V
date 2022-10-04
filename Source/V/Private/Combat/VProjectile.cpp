#include "Combat/VProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

AVProjectile::AVProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereC = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereC->SetCollisionProfileName("Projectile");

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
}

void AVProjectile::AddActorToIgnore(AActor* Actor)
{
	SphereC->IgnoreActorWhenMoving(Actor, true);
}
