#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "VCharacter.generated.h"

class UVInteractionComponent;
class AVProjectile;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class V_API AVCharacter : public ACharacter
{
	GENERATED_BODY()

protected: // Components
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraC;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmC;

	UPROPERTY(VisibleAnywhere)
	UVInteractionComponent* InteractionC;

public:
	AVCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected: // Input References
	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<AVProjectile> PrimaryProjectile;

protected: // Input
	void MoveForward(float Value);

	void MoveRight(float Value);

	void AttackPrimary();

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
