#include "Core/VCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AVCharacter::AVCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmC = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraC	   = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	SpringArmC->SetupAttachment(RootComponent);
	CameraC->SetupAttachment(SpringArmC);
}

// Called when the game starts or when spawned
void AVCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AVCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
