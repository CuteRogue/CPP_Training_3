// Fill out your copyright notice in the Description page of Project Settings.


#include "Moveable.h"

// Sets default values for this component's properties
UMoveable::UMoveable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UMoveable::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
}

// Called every frame
void UMoveable::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TryMoveObjectToOffset(DeltaTime);
}

void UMoveable::TryMoveObjectToOffset(const float DeltaTime)
{
	FVector TargetLocation = OriginalLocation;
	if (ShouldMove)
	{
		TargetLocation = OriginalLocation + MoveOffset;
	}
	
	const FVector CurrentLocation = GetOwner()->GetActorLocation();
	const float Speed = MoveOffset.Length() / MoveTime;

	const FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);
}

void UMoveable::ActivateMove()
{
	ShouldMove = true;
}

void UMoveable::DeactivateMove()
{
	ShouldMove = false;
}



