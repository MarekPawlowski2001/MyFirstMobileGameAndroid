// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TheOneGameModeBase.h"
#include "MasterGameInstance.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstance.h"
#include "Sound/SoundBase.h"
#include "Engine/Font.h"
#include "GameFramework/PlayerStart.h"
#include "Components/TextRenderComponent.h"
#include "CubePawn.generated.h"

UCLASS()
class THEONE_API ACubePawn : public APawn
{
	GENERATED_BODY()
	// Scale of the 3D mesh
		FVector ScaleCube {0.5,0.5,0.5};
public:
	// Sets default values for this pawn's properties
	//Default score
	int Score{0};
	// Default goal, display in Gameplay UserWidget
	UPROPERTY(BlueprintReadWrite)
	int Goal{};
	// Pointer to mesh component
	UPROPERTY(EditAnywhere)	
	UStaticMeshComponent* CubePawnVisual;
	// Pointer to the text component with score on the player pawn
	UPROPERTY(EditAnywhere)	
	UTextRenderComponent* ScoreText;
	// object use to check collision with squares 
	FCollisionShape SmallBox{};
	// calculate the time between level start and level end
	UPROPERTY()
	float timer{};
	// string to show the time when level ends
	UPROPERTY(BlueprintReadWrite)
	FString LevelCompletedString{};
	// Set the proper time when level ends
	UFUNCTION(BlueprintCallable)
	void SetLevelCompletedString();
	// Save the information where touch begin
	FVector TouchStartLocation{};
	// Check only first touch on multi touch smartphones
	ETouchIndex::Type TouchStartIndex{};
	

	ATheOneGameModeBase* ActiveGameMode{};
	UMasterGameInstance* ActiveGameInstance{};
	APlayerController* AcitvePlayerController{};
	AGameplayHUD* ActiveGameHUD{};
	
	
	ACubePawn();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Move the player pawn
	void Up();
	void Down();
	void Right();
	void Left();
	// Calculate the swipe direction
	void TouchBegin(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchEnd(ETouchIndex::Type FingerIndex, FVector Location);
	// exit and back to the menu
	void BackInput();
	// detect colision and calculate new score if neccesery 
	void Collision();
	// check if move is legal
	bool IsThereABasePlane(FVector location);
	void ResetPawn(int A);
};
