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
	UVInteractionComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(
		float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};