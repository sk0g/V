#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"

#include "VInteractionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class V_API UVInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void Interact();

public:
	// Sets default values for this component's properties
	UVInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
