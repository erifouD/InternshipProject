// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "IntershipSwipeStGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllerBase.h"
#include "LevelCreator.h"
#include "Components/SplineMeshComponent.h"
#include "PlayerPawnBase.generated.h"

UCLASS()
class INTERSHIPSWIPEST_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

	//Default player camera
	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* PawnCamera;

	//Checking for tap
	bool bIsTapHold = false;

	UPROPERTY(BlueprintReadWrite)
	FVector CurrentCursorLocation;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void ActionPressed();

	UFUNCTION()
	void ActionReleased();

	UFUNCTION()
	void RecievingLocation();

};
