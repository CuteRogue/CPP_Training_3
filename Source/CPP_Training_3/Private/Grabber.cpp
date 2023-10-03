// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

// Called every frame
void UGrabber::TickComponent(const float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{ return; }

	if (UPrimitiveComponent* Component = PhysicsHandle->GetGrabbedComponent(); Component != nullptr)
	{
		Component->WakeAllRigidBodies();
		
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabber::Grab()
{
	// Debug Test grab
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Grab"));

	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{ return; }

	if (FHitResult HitResult; CheckGrabableInReach(HitResult))
	{
		// Debug Test hit
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("HIT: %s"), *HitResult.GetActor()->GetActorNameOrLabel()));
		//DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, false, 5);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);

		HitResult.GetActor()->Tags.Add("Grabbed");
		HitResult.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		
		HitResult.GetComponent()->SetSimulatePhysics(true);
		HitResult.GetComponent()->WakeAllRigidBodies();
		
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

void UGrabber::Release()
{
	// Debug Test release
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Release"));

	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{ return; }

	if (UPrimitiveComponent* Component = PhysicsHandle->GetGrabbedComponent(); Component != nullptr)
	{
		Component->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();

		Component->GetOwner()->Tags.Remove(("Grabbed"));
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

bool UGrabber::CheckGrabableInReach(FHitResult &HitResult)
{
	const FVector Start = GetComponentLocation();
	const FVector End = Start + (GetForwardVector() * MaxGrabDistance);
	//DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	//DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);
	
	return GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(GrabRadius)
	);
}

