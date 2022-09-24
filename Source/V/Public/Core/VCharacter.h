#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VCharacter.generated.h"

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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
