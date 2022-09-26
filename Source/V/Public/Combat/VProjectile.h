#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class V_API AVProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVProjectile();

public: // Projectile properties
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = 200, UIMax = 2000))
	float ForwardMovementSpeed = 800.f;

	UPROPERTY(EditDefaultsOnly)
	bool bAffectedByGravity = false;

protected: // Components
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereC;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementC;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleC;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
