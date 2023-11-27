// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "Containers/UnrealString.h"
#include "GameplayHUD.h"
#include "BasePlane.h"
#include "Level0PlayerController.h"
#include "TheOneGameModeBase.generated.h"
/**
 * 
 */
UCLASS()
class THEONE_API ATheOneGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		ATheOneGameModeBase();
public:
	// Goal is used to generate new goal or get the goal from saved and after that set the goal in cubePawn.h
	int Goal{};
	//Table used only  in GenerateRandomNubers     Easy				Medium					  Hard
	int Settings_Diff[3][10] = { {2,7,19,11,18,0,0,0,0,0},{2,6,16,10,15,11,11,3,0,0},{2,6,19,9,18,10,8,6,10,5} };
	//Pointers to all 25 squares to mark them when numbers were picked up after the goal was set up (used in ResetActiveLevel() and IsLevelEnds()
	ABasePlane* Planes [24];
	// PlanesIterator - holds the number of squares to Planes table, NumbersToPick - used to save numbers left to pick up, PreviousScore - used to reset the score on the player pawn (CubePawn.cpp)
	int PlanesIterator{}, NumbersToPick{24}, PreviousScore{};
	// Holds text with numbers in Game Mode to simulate the gameplay
	FText RandomNumbers[5][5];

	FRandomStream RandomInts{};
	// Helps simulating the gameplay to set up new goal
	int GameState[5][5];
	
	TArray<FText*> CanBePicked{};  


	virtual void StartPlay() override;
	// Check if the gameplay was saved for selected difficulty
	void IsGameStateSaved();
	// Reset the level, called from userwidget gameplay blueprint
	UFUNCTION(BlueprintCallable)
	void ResetActiveLevel();
	void IsLevelEnds();
	// Generate numbers on squares
	void GenerateRandomNumbers();
	void CheckAvailableFields(int i, int j);
	// Generate new goal
	void SetTheNewGoal();
	// Save all inforamtion about level 
	void SaveGameState();
};
