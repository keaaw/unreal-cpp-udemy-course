// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	auto parentActor = GetOwner()->GetParentActor();
	auto objName = GetOwner()->GetName();
	auto rotation = GetOwner()->GetActorRotation();
	UE_LOG(LogTemp, Warning, TEXT("KMW:UOpenDoor::BeginPlay: objName:%s rotation:%s"), *objName, *rotation.ToString())
	// rotation.Pitch += 45;
	// rotation.Yaw -= 60;
	// GetOwner()->SetActorRotation(rotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

