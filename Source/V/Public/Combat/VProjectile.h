#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE5Coro.h"

#include "VProjectile.generated.h"

class AVCharacter;
class UNiagaraSystem;
class UProjectileMovementComponent;
class USphereComponent;

using namespace UE5Coro;

UCLASS()
class V_API AVProjectile : public AActor
{
	GENERATED_BODY()

	friend AVCharacter;

public:
	AVProjectile();

protected:
	virtual void BeginPlay() override;

protected: // Components & references
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* ProjectileParticleC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* HitParticleC;

	/* The actor that fired this projectile */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile|References")
	AActor* FiredBy;

protected: // Movement
	/* The forward movement speed of the projectile, in cm/s */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = 200, UIMax = 2000), Category = "Projectile|Movement")
	float ForwardMovementSpeed = 800.f;

	/* If true, affected by gravitational forces */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile|Movement")
	bool bAffectedByGravity = false;

	/* If true, this projectile will collide according to the "Projectile" profile */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile|Movement")
	bool bCanCollide = true;

	/* Conditionally enable collision (depending on bCanCollide,
	 * after enough time has passed to allow the projectile to travel outside the player's hitbox */
	UFUNCTION(BlueprintCallable, Category = "Projectile|Movement")
	FAsyncCoroutine EnableCollision();

	void SetupMovementComponent();

protected: // Lifetime
	/* Lifetime for projectile to spawn with, after which Destroy() is called
	 * If left at 0.f, will not expire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile|Lifetime")
	float Lifetime = 0.f;

	/* If true, characters can trigger an early termination (and any on-termination actions) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile|Lifetime")
	bool bSupportsEarlyTermination = false;

	/* After lifetime passes, self-destruct (if not already destroyed) */
	UFUNCTION(Category = "Projectile|Lifetime")
	FAsyncCoroutine ScheduleExpiry();

public:
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SetInstigator(AActor* Actor);

	/* Play hit/death particles, and destroy self */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Projectile|Lifetime")
	void SelfDestruct();
};