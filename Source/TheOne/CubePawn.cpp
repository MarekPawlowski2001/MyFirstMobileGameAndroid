// Fill out your copyright notice in the Description page of Project Settings.


#include "CubePawn.h"
#include "TheOneGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
ACubePawn::ACubePawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    // Set the 3D Mesh for player's pawn
    CubePawnVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'"));
    CubePawnVisual->SetStaticMesh(MeshAsset.Object);
    // Set the texture
    static ConstructorHelpers::FObjectFinder<UMaterial> MainMaterial(TEXT("Material'/Game/CubePawn_Material.CubePawn_Material'"));
    CubePawnVisual->SetMaterial(0,MainMaterial.Object);
    SetActorScale3D(ScaleCube);
    CubePawnVisual->SetRelativeScale3D(ScaleCube);
    // Create box for collision detection
    SmallBox = FCollisionShape::MakeBox(FVector(1, 1, 1));
    // Create a component to display player score on the object
    ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Score"));
	ScoreText->AttachToComponent(CubePawnVisual, FAttachmentTransformRules::KeepRelativeTransform);
	ScoreText->SetHorizontalAlignment(EHTA_Center);
	ScoreText->SetVerticalAlignment(EVRTA_TextCenter);
	ScoreText->SetTextRenderColor(FColor::Black);
    // Set the text font
    ConstructorHelpers::FObjectFinder<UFont>EngineFont(TEXT("Font'/Game/Quicksand_offline.Quicksand_offline'"));
    ScoreText->SetFont(EngineFont.Object);
	ScoreText->SetWorldLocation(GetActorLocation() + FVector(35, 5, 131));
	ScoreText->SetWorldRotation(GetActorRotation()+ FRotator(90,0,180));
    // Set the size of the text with player score2
    ScoreText->Text = FText::AsNumber(Score);
	switch (ScoreText->Text.ToString().Len()){
                case 1 :
                    ScoreText->SetXScale(12);
	                ScoreText->SetYScale(12);
                    break;
                case 2 :
                    ScoreText->SetXScale(10);
	                ScoreText->SetYScale(10);
                    break;
                case 3 :
                    ScoreText->SetXScale(6.5);
	                ScoreText->SetYScale(6.5);
                    break;
                case 4 :
                    ScoreText->SetXScale(5);
	                ScoreText->SetYScale(5);
                    break;
            }
}

// Called when the game starts or when spawned
void ACubePawn::BeginPlay()
{
    Super::BeginPlay();
    ActiveGameMode = static_cast<ATheOneGameModeBase*> (UGameplayStatics::GetGameMode(GetWorld()));
    ActiveGameInstance = static_cast<UMasterGameInstance*>(UGameplayStatics::GetGameInstance(GetWorld()));
    //Set the score and the goal from Game Mode
    Goal = ActiveGameMode->Goal;
    Score = ActiveGameMode->PreviousScore;
    ScoreText->Text = FText::AsNumber(Score);
	switch (ScoreText->Text.ToString().Len()){
                case 1 :
                    ScoreText->SetXScale(12);
	                ScoreText->SetYScale(12);
                    break;
                case 2 :
                    ScoreText->SetXScale(10);
	                ScoreText->SetYScale(10);
                    break;
                case 3 :
                    ScoreText->SetXScale(6.5);
	                ScoreText->SetYScale(6.5);
                    break;
                case 4 :
                    ScoreText->SetXScale(5);
	                ScoreText->SetYScale(5);
                    break;
            }
}

// Called every frame
void ACubePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // count time used when player complets the level
    timer+=DeltaTime;
}

// Called to bind functionality to input
void ACubePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    //Set the keyboard inputs
    PlayerInputComponent->BindAction("Up", EInputEvent::IE_Pressed, this, &ACubePawn::Up);
    PlayerInputComponent->BindAction("Down", EInputEvent::IE_Pressed, this, &ACubePawn::Down);
    PlayerInputComponent->BindAction("Right", EInputEvent::IE_Pressed, this, &ACubePawn::Right);
    PlayerInputComponent->BindAction("Left", EInputEvent::IE_Pressed, this, &ACubePawn::Left);
    //Set touch control
    PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ACubePawn::TouchBegin);
    PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ACubePawn::TouchEnd);
    // Set functionality for back button on phones
    PlayerInputComponent->BindAction("Back", EInputEvent::IE_Released, this, &ACubePawn::BackInput);

}

 //Move player pawn up if there is a square
void ACubePawn::Up() {
    FVector PawnLocation = GetActorLocation();
    PawnLocation.X += 200;
    // Check if the move is leggal
    if(ACubePawn::IsThereABasePlane(PawnLocation)){
    SetActorLocationAndRotation(PawnLocation, GetActorRotation(), false, 0, ETeleportType::None);
    ACubePawn::Collision();
    }
}

//Move player pawn down if there is a square
void ACubePawn::Down() {
    //
    FVector PawnLocation = GetActorLocation();
    PawnLocation.X -= 200;
    // Check if the move is leggal
    if(ACubePawn::IsThereABasePlane(PawnLocation)){
    SetActorLocationAndRotation(PawnLocation, GetActorRotation(), false, 0, ETeleportType::None);
    ACubePawn::Collision();
    }
}

//Move player pawn right if there is a square
void ACubePawn::Right() {
    FVector PawnLocation = GetActorLocation();
    PawnLocation.Y += 200;
    // Check if the move is leggal
    if(ACubePawn::IsThereABasePlane(PawnLocation)){
    SetActorLocationAndRotation(PawnLocation, GetActorRotation(), false, 0, ETeleportType::None);
    ACubePawn::Collision();
    }
}

//Move player pawn left if there is a square
void ACubePawn::Left() {
    FVector PawnLocation = GetActorLocation();
    PawnLocation.Y -= 200;
    // Check if the move is leggal
    if(ACubePawn::IsThereABasePlane(PawnLocation)){
    SetActorLocationAndRotation(PawnLocation, GetActorRotation(), false, 0, ETeleportType::None);
    ACubePawn::Collision();
    }
}

//Gets the location where touch begin
void ACubePawn::TouchBegin(ETouchIndex::Type FingerIndex, FVector Location){
    TouchStartLocation.X =Location.X;
    TouchStartLocation.Y =Location.Y; 
    TouchStartIndex = FingerIndex;
}

//Gets the location where touch ends and decide the direction of the swipe
void ACubePawn::TouchEnd(ETouchIndex::Type FingerIndex, FVector Location){
    TouchStartLocation.X = TouchStartLocation.X - Location.X;
    TouchStartLocation.Y = TouchStartLocation.Y - Location.Y;
    if(TouchStartLocation.X*TouchStartLocation.X+TouchStartLocation.Y*TouchStartLocation.Y>100 && TouchStartIndex==FingerIndex){
        if(UKismetMathLibrary::Abs(TouchStartLocation.X)>UKismetMathLibrary::Abs(TouchStartLocation.Y))
        {
            if(TouchStartLocation.X>0) ACubePawn::Left();
            if(TouchStartLocation.X<0) ACubePawn::Right();
        }
        else
        {
            if(TouchStartLocation.Y>0) ACubePawn::Up();
            if(TouchStartLocation.Y<0) ACubePawn::Down();
        }
    }
}

// Implements exit the app functionality or back to menu
void ACubePawn::BackInput(){
    if(UGameplayStatics::GetCurrentLevelName(GetWorld(),1) == FString("MainMenu")){
        UKismetSystemLibrary::QuitGame(GetWorld(),0,EQuitPreference::Quit,0);
    }
    else{
        UGameplayStatics::OpenLevel(GetWorld(), "MainMenu", true);
    }
}

// Check the collision with squares, update the score and proceed main gameplay logic
void ACubePawn::Collision() {
    //Checking the collision with square
    FVector First = GetActorLocation();
    FVector Second = GetActorLocation();
    First.Z = 0;
    Second.Z = 0;
    FHitResult CubeHit{};
    FCollisionQueryParams QueryParams{};
    if (GetWorld()->SweepSingleByChannel(CubeHit, First, Second, FQuat::Identity, ECC_WorldStatic, SmallBox, QueryParams))
    {
        AActor* HitActor = CubeHit.GetActor();
        UTextRenderComponent* TextComponent = HitActor->FindComponentByClass<UTextRenderComponent>();
        if (TextComponent and TextComponent!= ScoreText)
        {
        // Check if there is a number to be picked up on the square
        if(TextComponent->Text.ToString().Len() && TextComponent->IsVisible()!=false){
            // Play basic move sound when player picks up the number
            ActiveGameInstance->PlayMoveSound();
            // Disable the text for the player
            TextComponent->SetVisibility(false);
            // Calculate new player score
            FString PlaneText = TextComponent->Text.ToString();
            ActiveGameMode->Planes[ActiveGameMode->PlanesIterator++] = static_cast<ABasePlane*>(HitActor);
            char temp = PlaneText[0];
            switch (PlaneText[0]) {
                case '+':
                    PlaneText = PlaneText.Mid(1);
                    Score += FCString::Atoi(*PlaneText);
                    break;
                case '-':
                    PlaneText = PlaneText.Mid(1);
                    Score -= FCString::Atoi(*PlaneText);
                    break;
                case 0x00D7:
                    PlaneText = PlaneText.Mid(1);
                    if(PlaneText[0]=='('){
                        size_t length =PlaneText.Len();
                        PlaneText = PlaneText.Mid(1,length-2);
                    }
                    Score *= FCString::Atoi(*PlaneText);
                    break;
                case '/':
                    PlaneText = PlaneText.Mid(1);
                     if(PlaneText[0]=='('){
                        size_t length =PlaneText.Len();
                        PlaneText = PlaneText.Mid(1,length-2);
                    }
                    Score /= FCString::Atoi(*PlaneText);
                    break;
                default: 
                    break;
            }
            if(Score>=1000)
            Score = 999;
            else if (Score<=-1000)
            Score = -999;
            //Update the score text size
            ScoreText->SetText (FText::AsNumber(Score));
            switch (ScoreText->Text.ToString().Len()){
                case 1 :
                    ScoreText->SetXScale(12);
	                ScoreText->SetYScale(12);
                    break;
                case 2 :
                    ScoreText->SetXScale(10);
	                ScoreText->SetYScale(10);
                    break;
                case 3 :
                    ScoreText->SetXScale(6.5);
	                ScoreText->SetYScale(6.5);
                    break;
                case 4 :
                    ScoreText->SetXScale(5);
	                ScoreText->SetYScale(5);
                    break;
            }
            // Check if the score is equal to the goal and call the function from Game Mode
            if(Score == Goal){
                ActiveGameMode->IsLevelEnds();
            }
        }
        }
    }
}

//Check if the move is legal (move outside of 25 squares is illegal)
bool ACubePawn::IsThereABasePlane(FVector location){
    location.Z = 0;
    FHitResult CubeHit{};
    FCollisionQueryParams QueryParams{};
    return GetWorld()->SweepSingleByChannel(CubeHit, location, location, FQuat::Identity, ECC_WorldStatic, SmallBox, QueryParams);
}

//Reset the score to the previous one, reset the location to the center square and set the proper size of the score text
void ACubePawn::ResetPawn(int A){
    Score=A;
    ScoreText->SetText(FText::FromString(FString::FromInt(Score)));
    APlayerStart* PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));
        SetActorRotation(PlayerStart->GetActorRotation());
        SetActorLocation(PlayerStart->GetActorLocation());
    switch (ScoreText->Text.ToString().Len()){
                case 1 :
                    ScoreText->SetXScale(12);
	                ScoreText->SetYScale(12);
                    break;
                case 2 :
                    ScoreText->SetXScale(10);
	                ScoreText->SetYScale(10);
                    break;
                case 3 :
                    ScoreText->SetXScale(6.5);
	                ScoreText->SetYScale(6.5);
                    break;
                case 4 :
                    ScoreText->SetXScale(5);
	                ScoreText->SetYScale(5);
                    break;
            }
}

// Set the string after the level ends for WidgetUser with time how long does it take to completed the level
void ACubePawn::SetLevelCompletedString(){
    int Timer = static_cast<int>(timer);
    LevelCompletedString = "Level Completed in\n"+FString::FromInt(Timer/60)+" min "+FString::FromInt(Timer%60)+" sec";
}