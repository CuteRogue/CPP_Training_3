// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Moveable.h"
#include "Components/BoxComponent.h"
#include "HiddenDoorTriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_TRAINING_3_API UHiddenDoorTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UHiddenDoorTriggerComponent();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	AActor* KeyActor;

	UMoveable* TriggeredMoveable;

	TArray<AActor*> GetAcceptableActors() const;
	void ActivateHiddenDoor() const;
	void DeactivateHiddenDoor() const;
	
public:
	UFUNCTION(BlueprintCallable)
	void SetMoveable(UMoveable* Moveable);
};
