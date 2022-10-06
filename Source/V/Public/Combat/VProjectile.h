#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "VProjectile.generated.h"

class UNiagaraSystem;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class V_API AVProjectile : public AActor
{
	GENERATED_BODY()

public:
	AVProjectile();

protected:
	virtual void BeginPlay() override;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* ProjectileParticleC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* HitParticleC;

protected: // Helpers
	// TODO (UE5.1's coroutines): schedule execution of this within CPP
	//   This is called from BP for now, which is horrible.
	UFUNCTION(BlueprintCallable)
	void EnableCollision();
};