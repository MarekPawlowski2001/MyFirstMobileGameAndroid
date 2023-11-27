// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveSystem.h"
#include "AdMob.h"
#include "MasterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THEONE_API UMasterGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	// Pointers to all sounds
	UPROPERTY()
	USoundBase* MoveSFX{};
	UPROPERTY()
	USoundBase*	ClickSFX{};
	UPROPERTY()
	USoundBase* GoalSFX {};
	// Pointer to SaveSystem.h
	UPROPERTY(EditAnywhere)
	USaveSystem* ValidSave{};
	//Setting for all sounds
	UPROPERTY(BlueprintReadWrite)
	bool SoundSetting{};
	// Holds number of completed levels
	UPROPERTY(BlueprintReadWrite)
	int CompletedEasyLevels{1};
	UPROPERTY(BlueprintReadWrite)
	int CompletedMediumLevels{1};
	UPROPERTY(BlueprintReadWrite)
	int CompletedHardLevels{1};

	UPROPERTY(BlueprintReadWrite)
	int Difficulty{};
	UPROPERTY(BlueprintReadOnly)
	bool AreAdsRemoved{};


	UMasterGameInstance();
	// Open level from MainMenu blueprint
	UFUNCTION(BlueprintCallable)
		void LoadNewLevel();
	// Updates number of completed elvels 
	void LevelCompleted();
	// Change settings for sounds
	UFUNCTION(BlueprintCallable)
		void TurnOnSound();
	UFUNCTION(BlueprintCallable)
		void Mute();
	// Plays sounds
	void PlayMoveSound();
	UFUNCTION(BlueprintCallable)
		void PlayClickSound();
		void PlayGoalSound();
	// Update difficulty
	UFUNCTION(BlueprintCallable)
		void ChangeDifficultyRight();
	UFUNCTION(BlueprintCallable)
		void ChangeDifficultyLeft();
	// Check purchases status
	UFUNCTION(BlueprintCallable)
		void UpdatePurchase(bool DisableAdsWasPurchased);

	
	
	// Due to blueprint bug

	UFUNCTION(BlueprintCallable)
	static void MyShowBanner(int32 Index, bool isOnBottom);

	UFUNCTION(BlueprintCallable)
	static void MyHideBanner();

	UFUNCTION(BlueprintCallable)
	static void MyLoadInterstitialAd(int32 Index);

	UFUNCTION(BlueprintCallable)
	static void MyShowInterstitialAd();
};
