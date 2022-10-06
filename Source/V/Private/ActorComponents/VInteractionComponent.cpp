#include "ActorComponents/VInteractionComponent.h"

#include "Interfaces/VInteractable.h"

UVInteractionComponent::UVInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UVInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UVInteractionComponent::TickComponent(
	float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UVInteractionComponent::Interact()
{
	FVector TraceStart;
	FRotator ControlRotation;
	GetOwner()->GetActorEyesViewPoint(TraceStart, ControlRotation);
	FVector TraceEnd = TraceStart + (ControlRotation.Vector() * 200.f);

	FCollisionObjectQueryParams Params;
	Params.AddObjectTypesToQuery(ECC_WorldDynamic);
	Params.AddObjectTypesToQuery(ECC_WorldStatic);

	FCollisionShape Shape;
	Shape.SetCapsule(50.f, 50.f);

	TArray<FHitResult> Hits;
	GetWorld()->SweepMultiByObjectType(Hits, TraceStart, TraceEnd, FQuat::Identity, Params, Shape);

	for (auto HitResult : Hits)
	{
		if (not HitResult.GetActor()->Implements<UVInteractable>()) { continue; }
		IVInteractable::Execute_Interact(HitResult.GetActor(), GetOwner());
		return;
	}
}