// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineMeshComponent.h"
#include "SplineLine.generated.h"

UCLASS()
class INTERSHIPSWIPEST_API ASplineLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineLine();

	UPROPERTY()
	TArray<USplineMeshComponent*> ArrayLineSegments;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Function to create a spline point. Has an implementation in blueprint
	UFUNCTION(BlueprintImplementableEvent)
	void AddSplineElement(float x, float y);

	UFUNCTION(BlueprintCallable)
	void AddSplineMeshToArray(USplineMeshComponent* Mesh);
	
};
