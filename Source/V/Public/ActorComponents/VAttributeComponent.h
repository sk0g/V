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
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Value;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float Max;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent Changed;

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

	UPROPERTY(BlueprintReadWrite, Instanced, EditAnywhere)
	UVAttribute* Health;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent HealthChanged;
};