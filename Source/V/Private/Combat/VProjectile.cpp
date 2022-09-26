#include "Combat/VProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AVProjectile::AVProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereC = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereC->SetCollisionProfileName("Projectile");

	RootComponent = SphereC;

	ParticleC = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComponent");
	ParticleC->SetupAttachment(SphereC);

	MovementC								= CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementC->InitialSpeed					= ForwardMovementSpeed;
	MovementC->bRotationFollowsVelocity		= true;
	MovementC->bInitialVelocityInLocalSpace = true;
	if (not bAffectedByGravity)
	{
		MovementC->ProjectileGravityScale = 0.f;
	}
}

// Called when the game starts or when spawned
void AVProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
