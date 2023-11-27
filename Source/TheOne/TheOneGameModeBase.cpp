// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheOneGameModeBase.h"
#include "CubePawn.h"
#include "Math/UnrealMathUtility.h"

ATheOneGameModeBase::ATheOneGameModeBase():Super() {
	// set default pawn, controller, hud class
	DefaultPawnClass = ACubePawn::StaticClass();
	PlayerControllerClass = ALevel0PlayerController::StaticClass();
	HUDClass = AGameplayHUD::StaticClass();
}

void ATheOneGameModeBase::StartPlay(){
	// set the unlite mode
	GetWorld()->GetGameViewport()->ViewModeIndex = 2;
	// check the saved maps
	IsGameStateSaved();
	Super::StartPlay();
}

// check if there is a saved game for selected difficulty level
void ATheOneGameModeBase::IsGameStateSaved(){
	UMasterGameInstance* ActiveGameInstance = static_cast<UMasterGameInstance*>(UGameplayStatics::GetGameInstance(GetWorld()));
	switch (ActiveGameInstance->Difficulty){
		case 0:
			if(ActiveGameInstance->ValidSave->IsSaveEasyActive){
				//Set the numbers from Save to the Game Mode
				for(int i{}; i<5; i++){
					for(int j{}; j<5; j++){
						RandomNumbers[i][j] = ActiveGameInstance->ValidSave->SaveEasy[5*i+j];
					}
				}
				Goal = ActiveGameInstance->ValidSave->EasyGoal;
				PreviousScore = ActiveGameInstance->ValidSave->EasyScore;
				NumbersToPick = ActiveGameInstance->ValidSave->EasyPlanesToPickUp;
			}
			else GenerateRandomNumbers();
			break;
		case 1:
			if(ActiveGameInstance->ValidSave->IsSaveMediumActive){
			//Set the numbers from Save to the Game Mode
			for(int i{}; i<5; i++){
				for(int j{}; j<5; j++){
						RandomNumbers[i][j] = ActiveGameInstance->ValidSave->SaveMedium[5 * i + j];
					}
				}
				Goal = ActiveGameInstance->ValidSave->MediumGoal;
				PreviousScore = ActiveGameInstance->ValidSave->MediumScore;
				NumbersToPick = ActiveGameInstance->ValidSave->MediumPlanesToPickUp;
			}
			else GenerateRandomNumbers();
			break;
		case 2:
			if(ActiveGameInstance->ValidSave->IsSaveHardActive){
				//Set the numbers from Save to the Game Mode
				for(int i{}; i<5; i++){
					for(int j{}; j<5; j++){
						RandomNumbers[i][j] = ActiveGameInstance->ValidSave->SaveHard[5 * i + j];
					}
				}
				Goal = ActiveGameInstance->ValidSave->HardGoal;
				PreviousScore = ActiveGameInstance->ValidSave->HardScore;
				NumbersToPick = ActiveGameInstance->ValidSave->HardPlanesToPickUp;
			}
			else GenerateRandomNumbers();
			break;
	}
}

// Function called from the userwidget gameplay blueprint
void ATheOneGameModeBase::ResetActiveLevel(){
	for(int i{}; i<PlanesIterator;i++){
		//Reset proper planes
		Planes[i]->ResetTextComponent();
	}
	PlanesIterator = 0;
	//Rest player pawn
	ACubePawn* ActivePawn = static_cast <ACubePawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ActivePawn->ResetPawn(PreviousScore);
}

// Function called when score == goal from cubepawn.h
void ATheOneGameModeBase::IsLevelEnds(){
	UMasterGameInstance* ActiveGameInstance = static_cast<UMasterGameInstance*>(UGameplayStatics::GetGameInstance(GetWorld()));
	ActiveGameInstance->PlayGoalSound();
	NumbersToPick-=PlanesIterator;
	if(0 == NumbersToPick) {
		//end the level
		UGameplayStatics::GetPlayerController(GetWorld(),0)->SetPause(1);
		ActiveGameInstance->LevelCompleted();
		static_cast<AGameplayHUD*> (UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD())->LevelEnd();
		}
	else{
		// Set the new goal
		for(int i{}; i<PlanesIterator; i++){
			FVector Location = Planes[i]->GetActorLocation();
			RandomNumbers[2-static_cast<int>(Location.X)/200][2+static_cast<int>(Location.Y)/200] = FText::GetEmpty();
		}
		// Save new game state in SetTheNewGoal() function
		PlanesIterator = 0;
		PreviousScore = Goal;
		SetTheNewGoal();
		static_cast <ACubePawn*>(GetWorld()->GetFirstPlayerController()->GetPawn())->Goal=Goal;
	}
	}

//Number Generator
void ATheOneGameModeBase::GenerateRandomNumbers(){
	int diff = static_cast<UMasterGameInstance*>(UGameplayStatics::GetGameInstance(GetWorld()))->Difficulty;
	RandomInts = FMath::Rand();
	for(int i{}; i<5;i++){
		for(int j{}; j<5;j++){
			if(i!=2 || j!=2){
				int k=RandomInts.RandRange(0,10);
				if(k< Settings_Diff[diff][0]){
					RandomNumbers[i][j]=FText::FromString(TEXT(""));
					NumbersToPick--;
				}
				else if(k< Settings_Diff[diff][1]){
					RandomNumbers[i][j]=FText::FromString(FString("+") + FString::FromInt(RandomInts.RandRange(1, Settings_Diff[diff][2])));
				}
				else if(k< Settings_Diff[diff][3]){
					RandomNumbers[i][j]=FText::FromString(FString("-") + FString::FromInt(RandomInts.RandRange(1, Settings_Diff[diff][4])));
				}
				else if(k< Settings_Diff[diff][5]){
					int l=RandomInts.RandRange(0,10);
					if (l< Settings_Diff[diff][6])
						// \u00D7 is multipliaction symbol
						RandomNumbers[i][j]=FText::FromString(FString(TEXT("\u00D7")) +FString::FromInt(RandomInts.RandRange(2, Settings_Diff[diff][7])));
					else 
						RandomNumbers[i][j]=FText::FromString(FString(TEXT("\u00D7")) + FString("(") +FString::FromInt(RandomInts.RandRange(-Settings_Diff[diff][7],-1))+ FString(")"));
				}
				else if(k== Settings_Diff[diff][8]){
					RandomNumbers[i][j]=FText::FromString(FString("/") +FString::FromInt(RandomInts.RandRange(1, Settings_Diff[diff][9])));
				}

			}
		}
    }
// Set the new goal and save generated numbers
	SetTheNewGoal();
}

// Helper function to generate goal number. Simulates which squares are available for player
void ATheOneGameModeBase::CheckAvailableFields(int i, int j){
	if(0<=i && i<5 && 0<=j && j<5 && GameState[i][j]!=1){
		if (RandomNumbers[i][j].EqualTo(FText::GetEmpty())){
			GameState[i][j] =1;
			CheckAvailableFields(i,j-1);
			CheckAvailableFields(i,j+1);
			CheckAvailableFields(i-1,j);
			CheckAvailableFields(i+1,j);
		}
		else if (GameState[i][j]==2){
			GameState[i][j]=1;
			CheckAvailableFields(i,j-1);
			CheckAvailableFields(i,j+1);
			CheckAvailableFields(i-1,j);
			CheckAvailableFields(i+1,j);
		}
		else {
			GameState[i][j] =1;
			CanBePicked.Add(&(RandomNumbers[i][j]));
		}
	}
}

//Generate goal number
void ATheOneGameModeBase::SetTheNewGoal(){
	for(int i{};i<5;i++)
		for(int j{};j<5;j++)
			GameState[i][j]=0;
	//Check which squares are available
	CheckAvailableFields(2,2);
	for(int i{};i<FMath::RandRange(3,8);i++){
		if(CanBePicked.Num()){
		int k = RandomInts.RandRange(0, CanBePicked.Num()-1);
		// Calculate temporary goal
		FString PlaneText = CanBePicked[k]->ToString();
        char temp = PlaneText[0];
        switch (PlaneText[0]) {
            case '+':
                PlaneText = PlaneText.Mid(1);
                Goal += FCString::Atoi(*PlaneText);
                break;
            case '-':
                PlaneText = PlaneText.Mid(1);
                Goal -= FCString::Atoi(*PlaneText);
                break;
            case 0x00D7:
                PlaneText = PlaneText.Mid(1);
                if(PlaneText[0]=='('){
                    size_t length =PlaneText.Len();
                    PlaneText = PlaneText.Mid(1,length-2);
                }
                Goal *= FCString::Atoi(*PlaneText);
                break;
            case '/':
                PlaneText = PlaneText.Mid(1);
                if(PlaneText[0]=='('){
                    size_t length =PlaneText.Len();
                    PlaneText = PlaneText.Mid(1,length-2);
                }
                Goal /= FCString::Atoi(*PlaneText);
			}
		if(Goal>=1000)
        	Goal = 999;
		else if (Goal <= -1000) {
			Goal = -999;
		}
		//mark used square in GameState table
		GameState[static_cast<int>(CanBePicked[k]-&(RandomNumbers[0][0]))/5] [(static_cast<int>(CanBePicked[k]-&(RandomNumbers[0][0])))%5] = 2;	
		CheckAvailableFields( static_cast<int>(CanBePicked[k]-&(RandomNumbers[0][0]))/5 , (static_cast<int>(CanBePicked[k]-&(RandomNumbers[0][0])))%5);
		CanBePicked.RemoveAt(k);
		}
	}
	//Save new goal and squares
	SaveGameState();
	CanBePicked.Empty();
}

// Save goal,previous score, all text on squares, mark save for difficulty as active, save number of squares with number  
void ATheOneGameModeBase::SaveGameState(){
	UMasterGameInstance* ActiveGameInstance = static_cast<UMasterGameInstance*>(UGameplayStatics::GetGameInstance(GetWorld()));
	switch (ActiveGameInstance->Difficulty){
		case 0:
			for(int i{}; i<5; i++){
				for(int j{}; j<5; j++){
					ActiveGameInstance->ValidSave->SaveEasy[5 * i + j] = RandomNumbers[i][j];
				}
			}
			ActiveGameInstance->ValidSave->EasyGoal = Goal;
			ActiveGameInstance->ValidSave->EasyScore = PreviousScore;
			ActiveGameInstance->ValidSave->IsSaveEasyActive = true;
			ActiveGameInstance->ValidSave->EasyPlanesToPickUp = NumbersToPick;
			break;
		case 1:
			for(int i{}; i<5; i++){
				for(int j{}; j<5; j++){
					ActiveGameInstance->ValidSave->SaveMedium[5 * i + j] = RandomNumbers[i][j];
				}
			}
			ActiveGameInstance->ValidSave->MediumGoal = Goal;
			ActiveGameInstance->ValidSave->MediumScore = PreviousScore;
			ActiveGameInstance->ValidSave->IsSaveMediumActive = true;
			ActiveGameInstance->ValidSave->MediumPlanesToPickUp = NumbersToPick;
			break;
		case 2:
			for(int i{}; i<5; i++){
				for(int j{}; j<5; j++){
					ActiveGameInstance->ValidSave->SaveHard[5 * i + j] = RandomNumbers[i][j];
				}
			}
			ActiveGameInstance->ValidSave->HardGoal = Goal;
			ActiveGameInstance->ValidSave->HardScore = PreviousScore;
			ActiveGameInstance->ValidSave->IsSaveHardActive = true;
			ActiveGameInstance->ValidSave->HardPlanesToPickUp = NumbersToPick;
			break;
		default:
			break;
	}
	UGameplayStatics::SaveGameToSlot(ActiveGameInstance->ValidSave,FString("Save_1.0"),0);
}