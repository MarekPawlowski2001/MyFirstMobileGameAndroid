// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayHUD.h"

AGameplayHUD::AGameplayHUD(){
	// set pointers to userwidget blueprints
	static ConstructorHelpers::FClassFinder<UUserWidget> Gameplay(TEXT("WidgetBlueprint'/Game/GamePlayWidget.GamePlayWidget_C'"));
	static ConstructorHelpers::FClassFinder<UUserWidget> Menu(TEXT("WidgetBlueprint'/Game/MainMenuWidget'"));
	static ConstructorHelpers::FClassFinder<UUserWidget> End(TEXT("WidgetBlueprint'/Game/EndLevelWidget.EndLevelWidget_C'"));
	
	GameplayWidget = CreateWidget<UUserWidget>(GetWorld(), Gameplay.Class);
	MainMenu = CreateWidget<UUserWidget>(GetWorld(), Menu.Class);
	EndLevel = CreateWidget<UUserWidget>(GetWorld(),End.Class);
}
void AGameplayHUD::BeginPlay(){
	//Display menu or gameplay userwidget
	if(UGameplayStatics::GetCurrentLevelName(GetWorld(),1) == FString("MainMenu")){
	MainMenu->AddToViewport();
	}
	else
	GameplayWidget->AddToViewport();
}

// Display end level widget and hide gameplay widget
void AGameplayHUD::LevelEnd(){
	if(GameplayWidget){
	if(GameplayWidget->IsInViewport())
	GameplayWidget->RemoveFromParent();
	}
	if(EndLevel)
	EndLevel->AddToViewport();
}