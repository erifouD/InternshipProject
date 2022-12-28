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

	//If the level is active
	if (bIsLevelCreatedPawn) {

		FHitResult Hit;

		UGameplayStatics::GetPlayerController(this, 0)->
			GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);

		FindEqualSphere(Hit.GetActor());




		//Is Valid Level Element
		if (IsValid(LevelCreatorInPawn)) {
			//If Click was on Sphere
			if (CalcLibrary::IsSphere(Hit.GetActor(), LevelCreatorInPawn) && 
				//And valid Sphere
				IsValid(LevelCreatorInPawn->DotsArray[SphereID])) {
				//If The Element is dot
				if (LevelCreatorInPawn->DotsArray.Num() == 1) {
					//If InLine created
					if (IsValid(InLinePtr))
						InLinePtr->Destroy();
					//Destroy point
					LevelCreatorInPawn->DotsArray[0]->Destroy();
					//Destroy level element
					LevelCreatorInPawn->Destroy();
				}
				else {
					FVector Util = Hit.GetActor()->GetActorLocation();
					//CalcLibrary::LineProjection(
					//	Hit.Location,
					//	LevelCreatorInPawn->DotsArray[SphereID]->GetActorLocation(),
					//	LevelCreatorInPawn->DotsArray[SphereID + 1]->GetActorLocation(),
					//	SphereID, CurrentSphere, LevelCreatorInPawn, InLinePtr
					//);

					InLinePtr = GetWorld()->SpawnActor<AInLineIndicator>(InLineClass, FTransform(FVector(Util.X, Util.Y, 50)));

					//Getting the ID for the clicked sphere
					SphereID = CalcLibrary::GetSphereIDFromArray(Hit.GetActor(), LevelCreatorInPawn);
					if (SphereID == 0) CurrentSphere = 0;
					else if (SphereID == LevelCreatorInPawn->DotsArray.Num() - 1) CurrentSphere = LevelCreatorInPawn->DotsArray.Num() - 1;
				}
			}
		}
	}
	bIsTapHold = true;
}

void APlayerPawnBase::ActionReleased()
{
	bIsTapHold = false;
	if(IsValid(InLinePtr))
		InLinePtr->Destroy();
	SphereID = 0;
	CurrentSphere = 0;
	LevelCreatorInPawn = nullptr;
}

void APlayerPawnBase::RecievingLocation()
{
	FHitResult Hit;
	UGameplayStatics::GetPlayerController(this, 0)->
		GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);

	CurrentCursorLocation = Hit.Location;

	//UpdatindInLineLocation
	LocationCalculation(Hit);
}



void APlayerPawnBase::LevelCreate()
{
	bIsLevelCreatedPawn = true;

	GameElementsArray = Cast<AIntershipSwipeStGameModeBase>(GetWorld()->GetAuthGameMode())->LevelsArray;
}

void APlayerPawnBase::LineInProgress(FHitResult Hit, int32 Multiplier)
{
	if (LevelCreatorInPawn != nullptr) {
		if (bIsLevelCreatedPawn && CurrentSphere + Multiplier < LevelCreatorInPawn->DotsArray.Num() && IsValid(InLinePtr)) {
			InLinePtr->SetActorLocation(CalcLibrary::LineProjection
			(CurrentCursorLocation,
				LevelCreatorInPawn->DotsArray[CurrentSphere]->GetActorLocation(),
				LevelCreatorInPawn->DotsArray[CurrentSphere + Multiplier]->GetActorLocation(),
				SphereID, CurrentSphere, LevelCreatorInPawn, InLinePtr)
			);
		}
	}
}

void APlayerPawnBase::FindEqualSphere(AActor* ComparableActor)
{
	if (IsValid(ComparableActor)) {
		if (CalcLibrary::IsSphere(ComparableActor, GameElementsArray[0])) {
			for (ALevelCreator* Iterator : GameElementsArray) {
				for (ASphereDot* SphereIterator : Iterator->DotsArray) {
					if (SphereIterator == ComparableActor) {
						LevelCreatorInPawn = Iterator;
						return;
					}
				}
			}
		}
	}
}


void APlayerPawnBase::LocationCalculation(FHitResult HitRes)
{

	CurrentCursorLocation = FVector(HitRes.Location.X, HitRes.Location.Y, 0);


	//If the pressed sphere is finite
	if (SphereID == 0) {
		LineInProgress(HitRes, 1);
	}

	//If the pressed sphere is back finite
	else if (SphereID == LevelCreatorInPawn->DotsArray.Num() - 1) {
		LineInProgress(HitRes, -1);
	}
}

