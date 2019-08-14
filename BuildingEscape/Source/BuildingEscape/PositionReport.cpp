// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReport.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	// ...
	auto objName = GetOwner()->GetName();
	auto objPosStr = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("KMW:UPositionReport::BeginPlay: objName:%s position:%s"), *objName, *objPosStr);
	GetOwner()->SetLifeSpan(2.5);
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// auto objName = GetOwner()->GetName();
	// auto result = GetOwner()->Destroy();
	// UE_LOG(LogTemp, Warning, TEXT("KMW: objName:%s result of destroy: %d"), *objName, result);

}

void UPositionReport::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	auto objName = GetOwner()->GetName();
	auto objPosStr = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("KMW:UPositionReport::OnComponentDestroyed: objName:%s bDestroyingHierarchy:%d"), *objName, bDestroyingHierarchy);

}



