// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterGameInstance.h"

UMasterGameInstance::UMasterGameInstance():Super(){
    //Check save file
    ValidSave = static_cast<USaveSystem*>(UGameplayStatics::CreateSaveGameObject(USaveSystem::StaticClass()));
	if(UGameplayStatics::DoesSaveGameExist(FString("Save_1.0"),0)){
		ValidSave = static_cast<USaveSystem*>(UGameplayStatics::LoadGameFromSlot(FString("Save_1.0"),0));
	}
    else{
        // init TArray for text with number for 25 squares
        ValidSave->SaveEasy.AddDefaulted(25);
        ValidSave->SaveMedium.AddDefaulted(25);
        ValidSave->SaveHard.AddDefaulted(25);
    }
    //Set the settings from save
	SoundSetting = ValidSave->Sound;
    CompletedEasyLevels = ValidSave->Easy;
    CompletedMediumLevels = ValidSave->Medium;
    CompletedHardLevels = ValidSave->Hard;
    Difficulty = ValidSave->SetDifficulty;
    AreAdsRemoved = ValidSave->AreAdsDisable;
    // Set SoundWave to USoundBase*
    static ConstructorHelpers::FObjectFinder<USoundBase> MoveSound(TEXT("SoundWave'/Engine/VREditor/Sounds/UI/Selection_Changes.Selection_Changes'"));
    static ConstructorHelpers::FObjectFinder<USoundBase> ClickSound(TEXT("SoundWave'/Game/SFX/Y2Mate_is-UI-Click-Sound-Effect-_FREE_-T_GjkD-vkdI-128k-1654527375074.Y2Mate_is-UI-Click-Sound-Effect-_FREE_-T_GjkD-vkdI-128k-1654527375074'"));
    static ConstructorHelpers::FObjectFinder<USoundBase> GoalSound(TEXT("SoundWave'/Game/SFX/LevelCompleted.LevelCompleted'"));
    MoveSFX = MoveSound.Object;
    ClickSFX = ClickSound.Object;
    GoalSFX = GoalSound.Object;

}

//Open level, called from Play button in MainMenu
void UMasterGameInstance::LoadNewLevel(){
    if (SoundSetting) {
        UGameplayStatics::PlaySound2D(this, ClickSFX);
    }
	UGameplayStatics::OpenLevel(GetWorld(), FName("Level0", false));
}
// Save information about number of completed levels
void UMasterGameInstance::LevelCompleted(){
    switch(Difficulty){
        case 0:
            CompletedEasyLevels++;
            ValidSave->Easy = CompletedEasyLevels;
            ValidSave->IsSaveEasyActive=false;
            break;
        case 1:
            CompletedMediumLevels++;
            ValidSave->Medium = CompletedMediumLevels;
            ValidSave->IsSaveMediumActive=false;
            break;
        case 2:
            CompletedHardLevels++;
            ValidSave->Hard = CompletedHardLevels;
            ValidSave->IsSaveHardActive=false;
            break;
        default:
            break; 
    }
    UGameplayStatics::SaveGameToSlot(ValidSave,FString("Save_1.0"),0);
}
//Mute all sounds
void UMasterGameInstance::Mute(){
    SoundSetting = false;
    ValidSave->Sound = false;
    UGameplayStatics::SaveGameToSlot(ValidSave,FString("Save_1.0"),0);
}
//TurnOn all sounds
void UMasterGameInstance::TurnOnSound(){
    SoundSetting = true;
    PlayClickSound();
    ValidSave->Sound = true;
    UGameplayStatics::SaveGameToSlot(ValidSave,FString("Save_1.0"),0);
}
//Play sound when click any button
void UMasterGameInstance::PlayClickSound(){
    if (SoundSetting)
        UGameplayStatics::PlaySound2D(this, ClickSFX);
}
//Play sound when new number from square is picked up
void UMasterGameInstance::PlayMoveSound(){
    if(SoundSetting)
        UGameplayStatics::PlaySound2D(this, MoveSFX);
}
// Play sound when goal == score
void UMasterGameInstance::PlayGoalSound() {
    if (SoundSetting)
        UGameplayStatics::PlaySound2D(this, GoalSFX);
}
// Called from arrow right, set up new difficulty
void UMasterGameInstance::ChangeDifficultyRight(){
    if(Difficulty<2){
        PlayClickSound();
        Difficulty++;
    }
    ValidSave->SetDifficulty = Difficulty;
    UGameplayStatics::SaveGameToSlot(ValidSave,FString("Save_1.0"),0);
}
// Called from arrow left, set up new difficulty
void UMasterGameInstance::ChangeDifficultyLeft(){
    if(Difficulty>0){
        PlayClickSound();
        Difficulty--;
    }
    ValidSave->SetDifficulty = Difficulty;
    UGameplayStatics::SaveGameToSlot(ValidSave,FString("Save_1.0"),0);

}
//Save purchasesto file and set AreAdsRemoved, called from userwidget MainMenu blueprint 
void UMasterGameInstance::UpdatePurchase(bool DisableAdsWasPurchased) {
    AreAdsRemoved = DisableAdsWasPurchased;
    ValidSave->AreAdsDisable = AreAdsRemoved;
    UGameplayStatics::SaveGameToSlot(ValidSave, FString("Save_1.0"), 0);
}

//Due to Blueprint bug

void UMasterGameInstance::MyShowBanner(int32 Index, bool bShowOnBottonOfScreen)
{
    FAdMobModule::AdMobShowBanner(Index, bShowOnBottonOfScreen);
}

void UMasterGameInstance::MyHideBanner() {
    FAdMobModule::AdMobHideBanner();
}

void UMasterGameInstance::MyLoadInterstitialAd(int32 Index) {
    FAdMobModule::AdMobLoadInterstitialAd(Index);
}

void UMasterGameInstance::MyShowInterstitialAd() {
    FAdMobModule::AdMobShowInterstitialAd();
}