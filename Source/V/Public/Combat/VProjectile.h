#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE5Coro.h"

#include "VProjectile.generated.h"

class UNiagaraSystem;
class UProjectileMovementComponent;
class USphereComponent;

using namespace UE5Coro;

UCLASS()
class V_API AVProjectile : public AActor
{
	GENERATED_BODY()

public:
	AVProjectile();

protected:
	virtual void BeginPlay() override;

protected: // Components
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereC;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* ProjectileParticleC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* HitParticleC;

protected: // Projectile properties/ references
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = 200, UIMax = 2000))
	float ForwardMovementSpeed = 800.f;

	UPROPERTY(EditDefaultsOnly)
	bool bAffectedByGravity = false;

	UPROPERTY(EditDefaultsOnly)
	bool bCanCollide = true;

public:
	UPROPERTY(VisibleAnywhere)
	AActor* FiredBy;

protected: // Helpers
	UFUNCTION(BlueprintCallable)
	FAsyncCoroutine EnableCollision();

public:
	UFUNCTION(BlueprintCallable)
	void SetInstigator(AActor* Actor);
};
