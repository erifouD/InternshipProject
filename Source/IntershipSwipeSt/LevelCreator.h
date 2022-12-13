// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SphereDot.h"
#include "LevelCreator.generated.h"


UCLASS()
class INTERSHIPSWIPEST_API ALevelCreator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelCreator();

	//An array of spheres on the playing field
	UPROPERTY()
	TArray<ASphereDot*> DotsArray;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
