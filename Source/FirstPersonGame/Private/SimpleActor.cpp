// First Person Game

#include "SimpleActor.h"

ASimpleActor::ASimpleActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(StaticMeshComponent);
}

void ASimpleActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASimpleActor::DoSomething()
{
	StaticMeshComponent->AddForce(FVector(0.0f, 0.0f, 100000.0f));
}