#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"

#include "VAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttributeChangedEvent, float, Current, float, Previous, float, Delta);

UCLASS(EditInlineNew, DefaultToInstanced, CollapseCategories)
class UVAttribute : public UObject
{
	GENERATED_BODY()

protected:
	/* Current value */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Value;

public:
	/* Maximum value to clamp to, minimum is 0 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float Max;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent Changed;

	/* Add a delta to the current value, returning whether result was clamped */
	UFUNCTION(BlueprintCallable)
	bool ApplyDelta(float Delta);
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class V_API UVAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UVAttributeComponent();

public: // Attributes
	UPROPERTY(BlueprintReadWrite, Instanced, EditAnywhere, Category = Attributes)
	UVAttribute* Health;

public: // Attribute Changed Events
	// NOTE: These get assigned to the in-attribute event, so runtime binding might not work
	// If so, the UVAttribute could scan for the events available in UVAttributeComponent, and call the correct one

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent HealthChanged;
};