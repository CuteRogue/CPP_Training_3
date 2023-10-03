// Fill out your copyright notice in the Description page of Project Settings.


#include "HiddenDoorTriggerComponent.h"

#include "Moveable.h"

UHiddenDoorTriggerComponent::UHiddenDoorTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHiddenDoorTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHiddenDoorTriggerComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TArray<AActor*> AcceptableActors = GetAcceptableActors(); AcceptableActors.Num() > 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("TEST: %i"), AcceptableActors.Num()));
		for (const auto Item : AcceptableActors)
		{
			if (UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Item->GetRootComponent()); Component != nullptr)
			{
				Component->SetSimulatePhysics(false);
				Item->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
			
		ActivateHiddenDoor();
	}
	else
	{
		DeactivateHiddenDoor();
	}
	
}

TArray<AActor*> UHiddenDoorTriggerComponent::GetAcceptableActors() const
{
	TArray<AActor*> Result;
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	
	for (const auto Item : OverlappingActors)
	{
		if (!Item->ActorHasTag("Grabbed"))
		{
			if (KeyActor == nullptr || Item == KeyActor)
			{
				Result.Add(Item);
			}
		}
	}

	return Result;
}


void UHiddenDoorTriggerComponent::ActivateHiddenDoor() const
{
	if (TriggeredMoveable == nullptr)
	{ return; }
	
	TriggeredMoveable->ActivateMove();
}

void UHiddenDoorTriggerComponent::DeactivateHiddenDoor() const
{
	if (TriggeredMoveable == nullptr)
	{ return; }
	
	TriggeredMoveable->DeactivateMove();
}

void UHiddenDoorTriggerComponent::SetMoveable(UMoveable* Moveable)
{
	TriggeredMoveable = Moveable;
}

