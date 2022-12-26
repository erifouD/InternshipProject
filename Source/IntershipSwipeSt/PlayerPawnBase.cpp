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
	if (bIsLevelCreatedPawn) {

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

	UGameplayStatics::GetPlayerController(this, 0)->
		GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);
	
	if (IsValid(LevelCreatorInPawn)) {
		if (Hit.GetActor()->GetClass() == LevelCreatorInPawn->SphereDotClass) {
			LocationCalculation(Hit);
		}
	}
}

double APlayerPawnBase::DistanceCalculation(FVector FirstPoint, FVector SecondPoint)
{
	//Vector Length Calculation
	return FMath::Sqrt((SecondPoint.X - FirstPoint.X) * (SecondPoint.X - FirstPoint.X) +
		(SecondPoint.Y - FirstPoint.Y) * (SecondPoint.Y - FirstPoint.Y));
}

FVector APlayerPawnBase::LineProjection(FVector CurrentLocation, FVector FirSphere, FVector SecSphere)
{
	double a, b, c, p, Height, SplineMeshDistance;

	//Finding the sides of a triangle
	a = DistanceCalculation(FirSphere, SecSphere);
	b = DistanceCalculation(CurrentLocation, FirSphere);
	c = DistanceCalculation(CurrentLocation, SecSphere);

	//Semiperimeter of a triangle
	p = (a + b + c) / 2;
	
	//Triangle Height
	Height = (2 * FMath::Sqrt(p * (p - a) * (p - b) * (p - c)) / a);

	SplineMeshDistance = FMath::Sqrt(b * b - Height * Height);

	FVector DistanceFromOrigin = FVector((SecSphere.X - FirSphere.X), (SecSphere.Y - FirSphere.Y), 0);
	FVector ShorterVector = DistanceFromOrigin * (SplineMeshDistance / a);
	FVector Final = FVector((ShorterVector.X + FirSphere.X), (ShorterVector.Y + FirSphere.Y), 0);
	return Final;
}

void APlayerPawnBase::LevelCreate()
{
	bIsLevelCreatedPawn = true;

	LevelCreatorInPawn = Cast<ALevelCreator>(Cast<AIntershipSwipeStGameModeBase>
		(GetWorld()->GetAuthGameMode())->NewLevel);
}

void APlayerPawnBase::LocationCalculation(FHitResult HitRes)
{
	int32 SphereID = 1;

	CurrentCursorLocation = FVector(HitRes.Location.X, HitRes.Location.Y, 0);

	//Getting the ID for the clicked sphere
	for (int i = 0; i < LevelCreatorInPawn->DotsArray.Num(); i++) {
		if (LevelCreatorInPawn->DotsArray[i] == HitRes.GetActor()) {
			SphereID = i;
			break;
		}
	}

	//If the pressed sphere is finite
	if (SphereID == 0 || SphereID == LevelCreatorInPawn->DotsArray.Num() - 1) {

		//If the distance is more than two
		if (DistanceCalculation(LevelCreatorInPawn->DotsArray[0]->GetActorLocation(), HitRes.Location) > 2) {
			FVector Util = LineProjection(HitRes.Location, LevelCreatorInPawn->DotsArray[0]->GetActorLocation(),
				LevelCreatorInPawn->DotsArray[1]->GetActorLocation());
			LevelCreatorInPawn->AddSphere(Util.X, Util.Y);
		}
	}
}

