// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Containers/UnrealString.h"
#include "Containers/Array.h"
#include "SaveSystem.generated.h"

/**
 * 
 */
UCLASS()
class THEONE_API USaveSystem : public USaveGame
{
    GENERATED_BODY()
public:
    // number of completed levels
    UPROPERTY(EditAnywhere)
    int Medium{};
    UPROPERTY(EditAnywhere)
    int Easy{};
    UPROPERTY(EditAnywhere)
    int Hard{};
    // sound settings
    UPROPERTY(EditAnywhere)
    bool Sound{ 1 };
    //selected difficulty from previous session
    UPROPERTY(EditAnywhere)
    int SetDifficulty{};
    // Check IAP
    UPROPERTY(EditAnywhere)
    bool AreAdsDisable{false};

    //Saved properties for easy difficulty
    UPROPERTY()
    bool IsSaveEasyActive{};
    UPROPERTY()
    int EasyScore{};
    UPROPERTY()
    int EasyGoal{};
    UPROPERTY()
    int EasyPlanesToPickUp{};
    UPROPERTY()
    TArray<FText> SaveEasy;

    //Saved properties for medium difficulty
    UPROPERTY()
    bool IsSaveMediumActive{};
    UPROPERTY()
    int MediumGoal{};
    UPROPERTY()
    int MediumScore{};
    UPROPERTY()
    int MediumPlanesToPickUp{};
    UPROPERTY()
    TArray<FText> SaveMedium;

    //Saved properties for hard difficulty
    UPROPERTY()
    bool IsSaveHardActive{};
    UPROPERTY()
    int HardGoal{};
    UPROPERTY()
    int HardScore{};
    UPROPERTY()
    int HardPlanesToPickUp{};
    UPROPERTY()
    TArray<FText> SaveHard;
};
