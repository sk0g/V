#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "VCharacter.generated.h"

enum class EAbilitySlot : uint8;
class UVInteractionComponent;
class AVProjectile;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class V_API AVCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AVCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected: // Components
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraC;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmC;

	UPROPERTY(VisibleAnywhere)
	UVInteractionComponent* InteractionC;

protected: // Input References
	UPROPERTY(EditAnywhere, Category = Combat)
	TMap<EAbilitySlot, TSubclassOf<AVProjectile>> Projectiles;

protected: // Input
	void MoveForward(float Value);

	void MoveRight(float Value);

	void Attack(EAbilitySlot Slot);
	DECLARE_DELEGATE_OneParam(FAttackDelegate, EAbilitySlot); // Allows templated input binding

protected: // Helpers
	/**
	 * @brief Get launch rotation for a projectile, to aim at the camera's center point
	 * @param LaunchLocation
	 * @return Rotation to launch projectile in, or ZeroRotator if crosshair isn't over a target
	 */
	FRotator GetCompensatedProjectileLaunchRotation(FVector LaunchLocation) const;
};