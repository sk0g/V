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

class V_API IVInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact(AActor* Instigator);
};
