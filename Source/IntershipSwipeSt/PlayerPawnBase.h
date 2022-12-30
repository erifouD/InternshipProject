// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LevelCreator.h"
#include "InLineIndicator.h"
#include "SphereDot.h"
#include "CalcLibrary.h"
#include "IntershipSwipeStGameModeBase.h"
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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AInLineIndicator> InLineClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASphereDot> SphereDotClass;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxDistance;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentLives = 3;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentLevelID;

	int32 TempScore = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 Score = 0;

	UPROPERTY(BlueprintReadOnly)
	AInLineIndicator* InLinePtr;

	UPROPERTY(BlueprintReadWrite)
	TArray<ALevelCreator*> GameElementsArray;

	UPROPERTY()
	int32 CurrentSphere;

	UPROPERTY()
	TArray<ASphereDot*> CheckedSpheres;

	UPROPERTY()
	FVector BestLocation;

	int32 SphereID = 0;

	UPROPERTY(BlueprintReadOnly)
	ALevelCreator* LevelCreatorInPawn;

	bool bIsLevelCreatedPawn = false;


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

	UFUNCTION(BlueprintCallable)
	void ActionReleased();

	UFUNCTION()
	void RecievingLocation();

	UFUNCTION()
	void LocationCalculation(FHitResult HitRes);

	UFUNCTION(BlueprintCallable)
	void LevelCreate();

	UFUNCTION()
	void LineInProgress(FHitResult Hit, int32 Multiplier);

	void FindEqualSphere(AActor* ComparableActor);

	UFUNCTION(BlueprintImplementableEvent)
	void Lose();

	UFUNCTION(BlueprintImplementableEvent)
	void DecreaseLife();

	UFUNCTION(BlueprintImplementableEvent)
	void AddScore();

	UFUNCTION(BlueprintPure)
	bool IsAllElementsDestroyed();

	UFUNCTION(BlueprintPure)
	bool bNoMoreLives();
};
