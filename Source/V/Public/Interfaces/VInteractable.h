#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "VInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UVInteractable : public UInterface
{
	GENERATED_BODY()

	void A();
};

/*
 * Interface for pawns and actors that can be interacted with
 */
class V_API IVInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Interact(AActor* Instigator);
};
