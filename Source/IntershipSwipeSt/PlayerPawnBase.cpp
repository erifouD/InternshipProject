// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include "Components/InputComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Adding Camera to Component
	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;

}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();

	//Setting camera rotation
	SetActorRotation(FRotator(-90, 0, 0));

	//Setting camera position
	SetActorLocation(FVector(0, 0, 1400));

	PawnCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	PawnCamera->SetOrthoWidth(2048);

	
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsTapHold)
		RecievingLocation();
}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("TapAction",
		IE_Pressed, this, &APlayerPawnBase::ActionPressed);

	PlayerInputComponent->BindAction("TapAction", 
		IE_Released, this, &APlayerPawnBase::ActionReleased);
}

void APlayerPawnBase::ActionPressed()
{
	bIsTapHold = true;

	//If the level is active
	if (Cast<AIntershipSwipeStGameModeBase>(GetWorld()->GetAuthGameMode())->bIsLevelCreated) {

		//Pawn Controller Variable
		APlayerController* PawnController = UGameplayStatics::GetPlayerController(this, 0);

		FHitResult Hit;

		PawnController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);
		FVector ClickLocation = Hit.Location;

		
	}
}

void APlayerPawnBase::ActionReleased()
{
	bIsTapHold = false;
}

void APlayerPawnBase::RecievingLocation()
{
	FHitResult Hit;

	ALevelCreator* LevelCreatorInPawn = Cast<ALevelCreator>(Cast<AIntershipSwipeStGameModeBase>
		(GetWorld()->GetAuthGameMode())->NewLevel);

	UGameplayStatics::GetPlayerController(this, 0)->
		GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);
	
	CurrentCursorLocation = FVector(Hit.Location.X, Hit.Location.Y, 0);
	if (IsValid(LevelCreatorInPawn)) {
		if (Hit.GetActor()->GetClass() == LevelCreatorInPawn->SphereDotClass) {
			TArray<USplineMeshComponent*> SplineLines = Cast<ASplineLine>(LevelCreatorInPawn->SplineLineClass)->ArrayLineSegments;
		}
	}
}

