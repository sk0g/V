#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"

#include "VInteractionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class V_API UVInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UVInteractionComponent();

	virtual void TickComponent(
		float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

public:
	void Interact();
};