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

		//Pawn Controller Variable
		APlayerController* PawnController = UGameplayStatics::GetPlayerController(this, 0);

		FHitResult Hit;

		PawnController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);

		//If the click was on a sphere
		if (IsValid(LevelCreatorInPawn)) {
			if (IsSphere(Hit.GetActor()) && IsValid(LevelCreatorInPawn->DotsArray[SphereID])) {
				FVector Util = LineProjection(Hit.Location, LevelCreatorInPawn->DotsArray[SphereID]->GetActorLocation(),
					LevelCreatorInPawn->DotsArray[SphereID + 1]->GetActorLocation());
				InLinePtr = GetWorld()->SpawnActor<AInLineIndicator>(InLineClass, FTransform(FVector(Util.X, Util.Y, 50)));

				//Getting the ID for the clicked sphere
				SphereID = GetSphereIDFromArray(Hit.GetActor());
				if (SphereID == 0) CurrentSphere = 0;
				else if (SphereID == LevelCreatorInPawn->DotsArray.Num() - 1) CurrentSphere = LevelCreatorInPawn->DotsArray.Num() - 1;
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

double APlayerPawnBase::DistanceCalculation(FVector FirstPoint, FVector SecondPoint)
{
	//Vector Length Calculation
	return FMath::Sqrt((SecondPoint.X - FirstPoint.X) * (SecondPoint.X - FirstPoint.X) +
		(SecondPoint.Y - FirstPoint.Y) * (SecondPoint.Y - FirstPoint.Y));
}

FVector APlayerPawnBase::LineProjection(FVector CurrentLocation, FVector FirSphere, FVector SecSphere)
{
	double a, b, c, p, Height, SplineMeshDistance, Angle;

	//Finding the sides of a triangle
	a = DistanceCalculation(FirSphere, SecSphere);
	b = DistanceCalculation(CurrentLocation, FirSphere);
	c = DistanceCalculation(CurrentLocation, SecSphere);

	//Semiperimeter of a triangle
	p = (a + b + c) / 2;
	
	//Triangle Height
	Height = (2 * FMath::Sqrt(p * (p - a) * (p - b) * (p - c)) / a);

	SplineMeshDistance = FMath::Sqrt(b * b - Height * Height);

	Angle = ((a * a + b * b - c * c) / (2 * b * a));
	FVector DistanceFromOrigin = FVector((SecSphere.X - FirSphere.X), (SecSphere.Y - FirSphere.Y), 0);

	if (Angle < 0)
		return FVector(FirSphere.X, FirSphere.Y, 50);

	else if ((SplineMeshDistance / a) < 1) {
		FVector ShorterVector = DistanceFromOrigin * (SplineMeshDistance / a);
		FVector Final = FVector((ShorterVector.X + FirSphere.X), (ShorterVector.Y + FirSphere.Y), 50);
		return Final;
	}

	else {
		OnNextSphere();
		return FVector(SecSphere.X, SecSphere.Y, 50);
	}
}

void APlayerPawnBase::LevelCreate()
{
	bIsLevelCreatedPawn = true;

	LevelCreatorInPawn = Cast<ALevelCreator>(Cast<AIntershipSwipeStGameModeBase>
		(GetWorld()->GetAuthGameMode())->NewLevel);
}

void APlayerPawnBase::LineInProgress(FHitResult Hit, int32 Multiplier)
{
	if (LevelCreatorInPawn != nullptr) {
		if (bIsLevelCreatedPawn && CurrentSphere + Multiplier < LevelCreatorInPawn->DotsArray.Num() && IsValid(InLinePtr)) {
			InLinePtr->SetActorLocation(LineProjection
			(CurrentCursorLocation,
				LevelCreatorInPawn->DotsArray[CurrentSphere]->GetActorLocation(),
				LevelCreatorInPawn->DotsArray[CurrentSphere + Multiplier]->GetActorLocation())
			);
		}

		//If the cursor is over a sphere
		//if (IsSphere(Hit.GetActor()) && LevelCreatorInPawn->DotsArray[CurrentSphere] != Hit.GetActor()) {
			//if (GetSphereIDFromArray(Hit.GetActor()) - CurrentSphere == Multiplier) {
				//if (CurrentSphere + Multiplier == 0 || CurrentSphere + Multiplier == LevelCreatorInPawn->DotsArray.Num() - 1) {
					//if (CurrentSphere + Multiplier > 0 || CurrentSphere + Multiplier < LevelCreatorInPawn->DotsArray.Num()) {
						//LevelCreatorInPawn->ClearLine();
						//InLinePtr->Destroy();
					//}
				//}
				//else CurrentSphere += Multiplier;
			//}
		//}
	}
}

int32 APlayerPawnBase::GetSphereIDFromArray(AActor* Sphere)
{
	if (Sphere->GetClass() == LevelCreatorInPawn->SphereDotClass) {
		for (int32 i = 0; i < LevelCreatorInPawn->DotsArray.Num(); i++) {
			if (LevelCreatorInPawn->DotsArray[i] == Sphere) {
				//SphereID = i;
				return i;
			}
		}
	}
	return -10;
}

bool APlayerPawnBase::IsSphere(AActor* HittedActor)
{
	if (HittedActor->GetClass() == LevelCreatorInPawn->SphereDotClass)
		return true;
	else return false;
}

void APlayerPawnBase::OnNextSphere()
{
	if (SphereID == 0) {
		if ((CurrentSphere + 1) == LevelCreatorInPawn->DotsArray.Num() - 1) {
			LevelCreatorInPawn->ClearLine();
			InLinePtr->Destroy();
		}
		else CurrentSphere++;
	}
	else {
		if ((CurrentSphere - 1) == 0) {
			LevelCreatorInPawn->ClearLine();
			InLinePtr->Destroy();
		}
		else CurrentSphere--;
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

