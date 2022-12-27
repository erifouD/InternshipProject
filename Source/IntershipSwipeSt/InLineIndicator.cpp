// Fill out your copyright notice in the Description page of Project Settings.


#include "InLineIndicator.h"

// Sets default values
AInLineIndicator::AInLineIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setting up Default Sphere
	RedDot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleSphere"));
}

// Called when the game starts or when spawned
void AInLineIndicator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInLineIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

