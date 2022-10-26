#include "ActorComponents/VAttributeComponent.h"

bool UVAttribute::ApplyDelta(float Delta)
{
	auto UnclampedNew = Value + Delta;
	auto ClampedNew	  = FMath::Clamp(UnclampedNew, 0.f, Max);

	Changed.Broadcast(ClampedNew, Value, Delta);
	Value = ClampedNew;
	return ClampedNew == UnclampedNew;
}

UVAttributeComponent::UVAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Health = CreateDefaultSubobject<UVAttribute>("HealthAttribute");
}

void UVAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	Health->Changed = HealthChanged;
}