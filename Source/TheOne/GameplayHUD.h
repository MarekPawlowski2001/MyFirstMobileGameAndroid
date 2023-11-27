// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameplayHUD.generated.h"

/**
 * 
 */
UCLASS()
class THEONE_API AGameplayHUD : public AHUD
{
	GENERATED_BODY()
public:
	// pointers to userwidget blueprint
	UPROPERTY()
	UUserWidget* GameplayWidget{};
	UPROPERTY()
	UUserWidget* MainMenu{};
	UPROPERTY()
	UUserWidget* EndLevel{};
	
	AGameplayHUD();
	virtual void BeginPlay() override;
	// call when level ends 
	void LevelEnd();
};
