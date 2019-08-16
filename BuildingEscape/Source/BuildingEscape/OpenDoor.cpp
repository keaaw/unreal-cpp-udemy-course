// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Engine/World.h"
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
	actorThatOpens_ = GetWorld()->GetFirstPlayerController()->GetPawn();
	doorOpen_ = false;
	steppedOffPlate_ = false;
}

void UOpenDoor::SetDoorRotation(float yawDegrees)
{
	auto rotation = GetOwner()->GetActorRotation();
	rotation.Yaw = yawDegrees;
	GetOwner()->SetActorRotation(rotation);

	auto objName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("KMW:UOpenDoor::setDoorRotation: objName:%s rotation:%s"), *objName, *rotation.ToString())
}

void UOpenDoor::OpenDoor()
{
	doorOpen_ = true;
	SetDoorRotation(openAngle_);
	auto objName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("KMW:UOpenDoor::OpenDoor: objName:%s"), *objName);
}

void UOpenDoor::CloseDoor()
{
	doorOpen_ = false;
	SetDoorRotation(0);
	auto objName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("KMW:UOpenDoor::CloseDoor: objName:%s"), *objName);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// poll the trigger volume
	// if the actor that opens is in the volume, then we open the door
	auto objName = GetOwner()->GetName();
	if (!doorOpen_ && pressurePlate_->IsOverlappingActor(actorThatOpens_))
	{
		OpenDoor();
		steppedOffPlate_ = false;
		UE_LOG(LogTemp, Warning, TEXT("KMW:UOpenDoor::TickComponent: objName:%s trigger door open"), *objName);
	}
	else if (doorOpen_ && !steppedOffPlate_ && !pressurePlate_->IsOverlappingActor(actorThatOpens_))
	{
		steppedOffPlate_ = true;
		lastDoorOpenTime_ = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("KMW:UOpenDoor::TickComponent: objName:%s step off plate at time %f"), *objName, lastDoorOpenTime_);
	}
	else if (doorOpen_ && steppedOffPlate_)
	{
		UE_LOG(LogTemp, Warning, TEXT("KMW:UOpenDoor::TickComponent: objName:%s in door close delay: time now %f"), *objName, GetWorld()->GetTimeSeconds());
		UE_LOG(LogTemp, Warning, TEXT("KMW:lastOpenTime = %f"), lastDoorOpenTime_);

		if (GetWorld()->GetTimeSeconds() >= lastDoorOpenTime_ + doorCloseDelay_)
			CloseDoor();
	}
}

