#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "VCharacter.generated.h"

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

public:
	// Sets default values for this character's properties
	AVCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
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
