// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
void AMainCamera::BeginPlay() {
	//set the gameplay camera
	APlayerController* RandomPlayer = UGameplayStatics::GetPlayerController(this, 0);
	RandomPlayer->SetViewTarget(this);
	GEngine->GameViewport->GetViewportSize(ViewportRes);
	AMainCamera::GetCameraComponent()->SetAspectRatio(ViewportRes.X/ViewportRes.Y<0.6? ViewportRes.X/ViewportRes.Y:0.6);
}